#ifndef PRIM_H
#define PRIM_H

#include "kruskal.h" // reuse MSTEdge / MSTResult, and (transitively) CSRData

// Runs Prim's MST algorithm directly on an already-prepared CSR
// representation of a weighted, undirected, connected graph, using a
// binary-heap priority queue. Starts from `startVertex` (recommended and
// defaulted to vertex 0, per section 2.1.2, for reproducibility).
MSTResult runPrim(const CSRData& csr, int V, int startVertex = 0);

#endif
