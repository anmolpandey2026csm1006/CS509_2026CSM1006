#!/usr/bin/env python3
"""
generate_color_tests.py

Generates random undirected, unweighted test graphs for Vertex Coloring
in the section 5.1 adjacency-list format:

    V E
    u0 degree n1 n2 ...

No self-loops, no duplicate parallel edges between the same pair. Keeps
large graphs sparse (E ~ 2V to 4V), per section 4.2.

Usage:
    python3 generate_color_tests.py
    python3 generate_color_tests.py --sizes 10 100 --outdir test
"""
import argparse
import os
import random


def build_undirected_graph(V, avg_extra_degree, seed):
    rng = random.Random(seed)
    adj = [set() for _ in range(V)]

    # Random spanning tree (not required for coloring, which tolerates
    # disconnected graphs, but keeps the graph reasonably interesting).
    for i in range(1, V):
        j = rng.randint(0, i - 1)
        adj[i].add(j)
        adj[j].add(i)

    extra_edges = int((V * avg_extra_degree) // 2)
    attempts = 0
    max_attempts = extra_edges * 5 + 1000
    added = 0
    while added < extra_edges and attempts < max_attempts:
        attempts += 1
        u = rng.randint(0, V - 1)
        v = rng.randint(0, V - 1)
        if u == v or v in adj[u]:
            continue
        adj[u].add(v)
        adj[v].add(u)
        added += 1

    return adj


def write_color_file(path, adj):
    V = len(adj)
    E = sum(len(nbrs) for nbrs in adj) // 2
    with open(path, "w") as f:
        f.write(f"{V} {E}\n")
        for u in range(V):
            nbrs = sorted(adj[u])
            f.write(f"{u} {len(nbrs)}" + ("".join(f" {n}" for n in nbrs)) + "\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sizes", nargs="+", type=int,
                     default=[10, 100, 10000, 50000, 100000])
    ap.add_argument("--outdir", default="test")
    ap.add_argument("--seed", type=int, default=51)
    args = ap.parse_args()

    os.makedirs(args.outdir, exist_ok=True)
    for size in args.sizes:
        avg_extra_degree = 2 if size > 1000 else 3
        adj = build_undirected_graph(size, avg_extra_degree, seed=args.seed + size)
        path = os.path.join(args.outdir, f"color_{size}.txt")
        write_color_file(path, adj)
        E = sum(len(a) for a in adj) // 2
        print(f"Wrote {path}  (V={size}, E={E})")


if __name__ == "__main__":
    main()
