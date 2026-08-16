# Assignment 03 – Minimum Spanning Tree (Kruskal & Prim)

This assignment is a part of the **CS509** laboratory coursework and consists of a single individual task:

- **Task 01:** Minimum Spanning Tree — both **Kruskal's algorithm** and **Prim's algorithm**, run on the same weighted, undirected, connected graph so their results and execution times can be compared directly.

---

# Assignment Structure

```
Assignment_03
│
├── Task_01                 (MST: Kruskal + Prim)
│   ├── driver/
│   ├── source/
│   ├── test/
│   ├── output/
│   └── Makefile
│
├── tools/                   (test-graph generator)
│   └── generate_mst_tests.py
│
├── common_wrapper.cpp
└── README.md
```

---

# Task 01 – Minimum Spanning Tree

`mstMain` reads a single weighted, undirected, connected graph and runs
**both** Kruskal's and Prim's algorithms on it, printing both result
blocks (edges, total weight, execution time) so they can be compared
directly, per section 5.3 of the assignment.

- **Kruskal's algorithm** extracts each undirected edge exactly once from
  the CSR structure (keeping only the copy seen from the lower-indexed
  endpoint), sorts the edge list by weight, and adds edges via a
  Disjoint-Set-Union (Union-Find, path compression + union by rank)
  structure, stopping once V-1 edges are selected. Per section 8 of the
  spec, the edge extraction and sort happen **inside** the timed
  `runKruskal()` call, since they are explicitly called out as part of
  Kruskal's algorithm proper.
- **Prim's algorithm** grows a single tree from vertex 0 (the
  spec-recommended, reproducible start) using a binary-heap priority
  queue over the CSR adjacency directly — no separate edge list is
  needed.
- Both algorithms are verified to report the **same total MST weight**
  on every test graph (see results table below); the specific edge sets
  can differ when a graph has more than one valid MST, which is expected
  and allowed by the spec.

### CSR reuse

Per the assignment instructions ("call the CSR conversion function from
the previous assignment, do not copy the code"), Task_01 does **not**
implement its own adjacency-list → CSR conversion. It includes and links
directly against `Assignment_01/Task_03/source/csr.h` / `csr.cpp` (the
`generateCSR()` helper and `CSRData` struct built in Assignment 1),
exactly as Assignment_02's Bellman-Ford task did. See
`Task_01/source/kruskal.h` and `Task_01/Makefile`.

---

# Compilation & Execution

```bash
cd Assignment_03
g++ common_wrapper.cpp -o wrapper_app
./wrapper_app
```

The wrapper provides a menu-driven interface to build, run the spec
example, run each required-size test case, run all test cases, or clean
generated binaries.

Alternatively, run the Makefile directly:

```bash
cd Task_01
make run-all
```

## Generating more test files

```bash
cd tools
python3 generate_mst_tests.py --outdir ../Task_01/test
```

The generator builds a random spanning tree first (guaranteeing
connectivity) and then adds extra random edges up to the target density
(E ≈ 2V–4V for large graphs, per section 4.2). Weights may be positive,
zero, or negative integers, matching section 5.1.

---

# MST Results

| File | V | E | Kruskal Weight | Prim Weight | Kruskal Time | Prim Time | Equal? | Status |
|---|---:|---:|---:|---:|---:|---:|:---:|:---:|
| mst_example.txt | 5 | 7 | 16 | 16 | 0.001167 ms | 0.001267 ms | Yes | ✅ Pass |
| mst_10.txt | 10 | 24 | -1 | -1 | 0.002121 ms | 0.004745 ms | Yes | ✅ Pass |
| mst_100.txt | 100 | 249 | 85 | 85 | 0.016592 ms | 0.025651 ms | Yes | ✅ Pass |
| mst_10000.txt | 10,000 | 19,999 | 18,920 | 18,920 | 1.11699 ms | 3.21277 ms | Yes | ✅ Pass |
| mst_50000.txt | 50,000 | 99,999 | 96,159 | 96,159 | 6.15169 ms | 19.3831 ms | Yes | ✅ Pass |
| mst_100000.txt | 100,000 | 199,999 | 192,769 | 192,769 | 12.6758 ms | 44.7051 ms | Yes | ✅ Pass |

All test cases completed successfully; both algorithms agreed on the
total MST weight at every graph size, including negative-weight edges
(the spec's example and `mst_10.txt` both include negative weights, and
the resulting total is correctly negative). No size resulted in
incomplete execution or a core-dump.

Kruskal is consistently faster than Prim on these sparse graphs (as
expected — Kruskal's O(E log E) sort dominates on sparse inputs, while
Prim's heap does more individual push/pop operations per edge relaxation
here), though both stay well under 50 ms even at V=100,000.

---

# Performance Notes

Execution time measurements include **only the algorithm execution
time**. The following are **excluded**:

- File reading
- Input parsing
- Adjacency-list → CSR conversion (shared, done once before either
  algorithm runs)
- Output generation

The following are **included** in Kruskal's timed region specifically,
per section 8 of the spec, since they are explicitly called out as part
of Kruskal's algorithm:

- Deduplicated edge-list extraction from the CSR structure
- Sorting the edge list by weight

---

# Technologies Used

- **Programming Language:** C++
- **Compiler:** GCC (g++)
- **Build System:** GNU Make
- **Platform:** Linux
