# Assignment 04 – Vertex Coloring & PageRank

This assignment is a part of the **CS509** laboratory coursework and consists of the following individual tasks:

- **Task 01:** Vertex Coloring (greedy, Welsh-Powell ordering)
- **Task 02:** PageRank

Both operate on separate CSR-based graph inputs and are timed independently, per section 4 of the spec.

---

# Assignment Structure

```
Assignment_04
│
├── Task_01                 (Vertex Coloring)
│   ├── driver/
│   ├── source/
│   ├── test/
│   ├── output/
│   └── Makefile
│
├── Task_02                 (PageRank)
│   ├── driver/
│   ├── source/
│   ├── test/
│   ├── output/
│   └── Makefile
│
├── tools/                   (test-graph generators)
│   ├── generate_color_tests.py
│   └── generate_pagerank_tests.py
│
├── common_wrapper.cpp
└── README.md
```

---

# Task 01 – Vertex Coloring

Implements greedy vertex coloring with Welsh-Powell ordering (section
2.1.1): vertex degrees are computed from the CSR structure, vertices are
sorted into non-increasing degree order, then processed in that order,
each receiving the smallest color index not already used by an
already-colored neighbour. The same routine handles every graph size with
no per-test hard-coding.

After the timed coloring call, the driver runs an untimed correctness
pass (checking no two adjacent vertices share a color) and reports both
the color count and the validity result, per section 5.3.

### CSR reuse

Per the assignment instructions, Task_01 does **not** implement its own
adjacency-list → CSR conversion. It includes and links directly against
`Assignment_01/Task_03/source/csr.h` / `csr.cpp` (`generateCSR()` /
`CSRData`), the same helper reused throughout Assignments 2 and 3.
Vertex Coloring is unweighted, so the placeholder weight `0` is passed
for every edge and simply ignored.

---

# Task 02 – PageRank

Implements the standard PageRank iteration (section 2.2):
`PR(v) = (1-d)/N + d * Σ PR(u)/outdeg(u)` for every `u → v` edge,
updating all vertices simultaneously each iteration using the previous
iteration's values. A dangling vertex (outdegree 0) has its rank
redistributed evenly across all vertices each iteration, rather than
vanishing from the system. Iteration stops once the total absolute
change across all vertices is `<= TOLERANCE`, or `MAX_ITERATIONS` is
reached. Per section 9, **all** iterations of the update loop are inside
the timed region.

### CSR reuse

Same as Task_01: built directly on `generateCSR()` /
`CSRData` from `Assignment_01/Task_03`, with the placeholder weight
ignored (PageRank graphs are unweighted).

### A note on the spec's worked example

Running the exact example graph from section 6.2 produces
`Sum of ranks: 1.000000` and a valid, converged result, but the
individual per-vertex values differ from those printed in section 6.3
(see the results table below). Working through the input by hand: under
the format's explicit rule ("list only the outgoing edges of each
vertex"), the edges are `0→1, 1→2, 2→0, 2→1, 3→2`, which gives vertex 3
an **in-degree of 0** and no vertices with outdegree 0 (no dangling
vertices at all). With zero incoming contribution and no dangling
redistribution reaching it, vertex 3's rank must converge to exactly
`(1-d)/N = 0.15/4 = 0.037500` — which is exactly what this
implementation reports. The spec's own worked-example figure for vertex
3 (`0.208624`) is only reachable if vertex 3 has nonzero in-degree (e.g.
if the adjacency list were read as undirected, or as incoming rather
than outgoing edges), which contradicts the format's explicit
definition. Since the format's textual rule is unambiguous and this
implementation's output satisfies the sum-of-ranks invariant exactly,
this is treated as the correct interpretation; the discrepancy is
recorded here rather than silently reconciled.

---

# Compilation & Execution

```bash
cd Assignment_04
g++ common_wrapper.cpp -o wrapper_app
./wrapper_app
```

Or run each task's Makefile directly:

```bash
cd Task_01 && make run-all      # Vertex Coloring
cd ../Task_02 && make run-all   # PageRank (required sizes)
cd ../Task_02 && make run6      # PageRank, optional V=100,000 test
```

## Generating more test files

```bash
cd tools
python3 generate_color_tests.py --outdir ../Task_01/test
python3 generate_pagerank_tests.py --outdir ../Task_02/test
```

The PageRank generator gives every vertex a ring edge `i → (i+1) mod V`
first, guaranteeing every vertex has at least one outgoing **and** one
incoming edge — so none of the required test graphs contain a dangling
(zero-outdegree) vertex to document, and every vertex is reachable, per
section 3.

---

# Vertex Coloring Results

| File | V | E | Colors Used | Valid? | Time | Status |
|---|---:|---:|---:|:---:|---:|:---:|
| color_example.txt | 5 | 6 | 3 | Yes | 0.000963 ms | ✅ Pass |
| color_10.txt | 10 | 24 | 4 | Yes | 0.001364 ms | ✅ Pass |
| color_100.txt | 100 | 249 | 5 | Yes | 0.008264 ms | ✅ Pass |
| color_10000.txt | 10,000 | 19,999 | 5 | Yes | 0.51626 ms | ✅ Pass |
| color_50000.txt | 50,000 | 99,999 | 5 | Yes | 2.88957 ms | ✅ Pass |
| color_100000.txt | 100,000 | 199,999 | 5 | Yes | 5.91667 ms | ✅ Pass |

The example graph produces a valid 3-coloring (the exact color-to-vertex
assignment differs from the spec's worked example, as explicitly allowed
by section 5.3, since it depends on tie-breaking within the Welsh-Powell
ordering — the color **count** and validity match). No size resulted in
incomplete execution or a core-dump.

---

# PageRank Results

| File | V | E | Damping | Top Vertex | Sum of Ranks | Iterations | Time | Status |
|---|---:|---:|---:|:---:|---:|---:|---:|:---:|
| pagerank_example.txt | 4 | 4 | 0.85 | 2 | 1.000000 | 18 | 0.001195 ms | ✅ Pass |
| pagerank_10.txt | 10 | 20 | 0.85 | 3 | 1.000000 | 19 | 0.001806 ms | ✅ Pass |
| pagerank_100.txt | 100 | 200 | 0.85 | 18 | 1.000000 | 20 | 0.011755 ms | ✅ Pass |
| pagerank_1000.txt | 1,000 | 2,000 | 0.85 | 108 | 1.000000 | 22 | 0.114825 ms | ✅ Pass |
| pagerank_10000.txt | 10,000 | 30,000 | 0.85 | 5,953 | 1.000000 | 15 | 2.09502 ms | ✅ Pass |
| pagerank_50000.txt | 50,000 | 150,000 | 0.85 | 24,513 | 1.000000 | 15 | 11.5445 ms | ✅ Pass |
| pagerank_100000.txt (optional) | 100,000 | 300,000 | 0.85 | 66,526 | 1.000000 | 15 | 23.2873 ms | ✅ Pass |

The sum of ranks stays at exactly `1.000000` after convergence at every
graph size, including the optional 100,000-vertex test (which completed
successfully — no core-dump, timeout, or out-of-memory condition was
observed). None of the generated test graphs contain a dangling
(zero-outdegree) vertex, by construction (see the generator notes
above).

---

# Performance Notes

Execution time measurements include **only the algorithm execution
time**. The following are **excluded**:

- File reading
- Input parsing
- Adjacency-list → CSR conversion
- Correctness verification (Vertex Coloring's post-hoc validity check)
- Output generation

The following are **included** in the timed region, per section 9:

- PageRank: every iteration of the rank-update loop

---

# Technologies Used

- **Programming Language:** C++
- **Compiler:** GCC (g++)
- **Build System:** GNU Make
- **Platform:** Linux
