#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
// Reuse the CSR conversion helper (generateCSR / CSRData) built in
// Assignment_01, Task_03. Per the Assignment_03 instructions we call the
// existing CSR conversion function rather than copy it into this
// assignment.
#include "../../../Assignment_01/Task_03/source/csr.h"

struct MSTEdge {
    int u, v;
    int weight;
};

struct MSTResult {
    std::vector<MSTEdge> edges;
    long long totalWeight = 0;
};

// Runs Kruskal's MST algorithm directly on an already-prepared CSR
// representation of a weighted, undirected, connected graph.
//
// Per section 8 of the spec ("if a sortable edge list is created from the
// already-prepared CSR inside the Kruskal routine, that extraction and
// edge sorting are part of Kruskal and must remain inside the timed
// algorithm call"), the deduplicated edge-list extraction and the sort
// both happen inside this function.
MSTResult runKruskal(const CSRData& csr, int V);

#endif
