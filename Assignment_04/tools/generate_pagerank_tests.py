#!/usr/bin/env python3
"""
generate_pagerank_tests.py

Generates random directed, unweighted test graphs for PageRank in the
section 6.1 adjacency-list format:

    V E
    u0 outdegree n1 n2 ...
    ...
    DAMPING d
    TOLERANCE epsilon
    MAX_ITERATIONS n

Every vertex i gets a ring edge i -> (i+1) % V first, guaranteeing every
vertex has at least one outgoing AND one incoming edge (so, per section 3,
"every vertex reachable by at least one incoming or outgoing edge" holds,
and there are no dangling/zero-outdegree vertices to document). Extra
random directed edges (self-loops excluded) are then added up to the
target density (E ~ 2V to 4V for large graphs).

Usage:
    python3 generate_pagerank_tests.py
    python3 generate_pagerank_tests.py --sizes 10 100 --outdir test
"""
import argparse
import os
import random


def build_directed_graph(V, avg_out_degree, seed):
    rng = random.Random(seed)
    adj = [set() for _ in range(V)]

    # Ring: guarantees every vertex has outdegree >= 1 and indegree >= 1.
    for i in range(V):
        adj[i].add((i + 1) % V)

    target_edges = V * avg_out_degree
    current_edges = sum(len(a) for a in adj)
    attempts = 0
    max_attempts = (target_edges - current_edges) * 5 + 1000
    while current_edges < target_edges and attempts < max_attempts and V > 1:
        attempts += 1
        u = rng.randint(0, V - 1)
        v = rng.randint(0, V - 1)
        if u == v or v in adj[u]:
            continue
        adj[u].add(v)
        current_edges += 1

    return adj


def write_pagerank_file(path, adj, damping, tolerance, max_iterations):
    V = len(adj)
    E = sum(len(nbrs) for nbrs in adj)
    with open(path, "w") as f:
        f.write(f"{V} {E}\n")
        for u in range(V):
            nbrs = sorted(adj[u])
            f.write(f"{u} {len(nbrs)}" + ("".join(f" {n}" for n in nbrs)) + "\n")
        f.write(f"DAMPING {damping}\n")
        f.write(f"TOLERANCE {tolerance}\n")
        f.write(f"MAX_ITERATIONS {max_iterations}\n")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sizes", nargs="+", type=int,
                     default=[10, 100, 1000, 10000, 50000])
    ap.add_argument("--outdir", default="test")
    ap.add_argument("--damping", type=float, default=0.85)
    ap.add_argument("--tolerance", type=float, default=0.0001)
    ap.add_argument("--max-iterations", type=int, default=100)
    ap.add_argument("--seed", type=int, default=61)
    args = ap.parse_args()

    os.makedirs(args.outdir, exist_ok=True)
    for size in args.sizes:
        avg_out_degree = 3 if size > 1000 else 2
        adj = build_directed_graph(size, avg_out_degree, seed=args.seed + size)
        path = os.path.join(args.outdir, f"pagerank_{size}.txt")
        write_pagerank_file(path, adj, args.damping, args.tolerance, args.max_iterations)
        E = sum(len(a) for a in adj)
        print(f"Wrote {path}  (V={size}, E={E})")


if __name__ == "__main__":
    main()
