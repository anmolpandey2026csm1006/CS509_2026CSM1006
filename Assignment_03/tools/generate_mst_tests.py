#!/usr/bin/env python3
"""
generate_mst_tests.py

Generates random connected, weighted, undirected test graphs for MST
(Kruskal & Prim) in the section 5.1 adjacency-list format:

    V E
    u0 degree n1 w1 n2 w2 ...
    ...

Connectivity is guaranteed by building a random spanning tree first (so
every vertex is reachable), then adding extra random edges up to the
target density (E ~ 2V to 4V, per section 4.2). Weights may be positive,
zero, or negative integers, per section 5.1.

Usage:
    python3 generate_mst_tests.py
    python3 generate_mst_tests.py --sizes 10 100 --outdir test
"""
import argparse
import os
import random


def build_connected_graph(V, avg_extra_degree, seed):
    rng = random.Random(seed)
    adj = [dict() for _ in range(V)]  # neighbor -> weight

    # Random spanning tree.
    for i in range(1, V):
        j = rng.randint(0, i - 1)
        w = rng.randint(-5, 20)
        adj[i][j] = w
        adj[j][i] = w

    # Extra random edges for density.
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
        w = rng.randint(-5, 20)
        adj[u][v] = w
        adj[v][u] = w
        added += 1

    return adj


def write_mst_file(path, adj):
    V = len(adj)
    E = sum(len(nbrs) for nbrs in adj) // 2
    with open(path, "w") as f:
        f.write(f"{V} {E}\n")
        for u in range(V):
            items = sorted(adj[u].items())
            parts = [f"{u} {len(items)}"]
            for v, w in items:
                parts.append(f"{v} {w}")
            f.write(" ".join(parts) + "\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sizes", nargs="+", type=int,
                     default=[10, 100, 10000, 50000, 100000])
    ap.add_argument("--outdir", default="test")
    ap.add_argument("--seed", type=int, default=31)
    args = ap.parse_args()

    os.makedirs(args.outdir, exist_ok=True)
    for size in args.sizes:
        avg_extra_degree = 2 if size > 1000 else 3
        adj = build_connected_graph(size, avg_extra_degree, seed=args.seed + size)
        path = os.path.join(args.outdir, f"mst_{size}.txt")
        write_mst_file(path, adj)
        E = sum(len(a) for a in adj) // 2
        print(f"Wrote {path}  (V={size}, E={E})")


if __name__ == "__main__":
    main()
