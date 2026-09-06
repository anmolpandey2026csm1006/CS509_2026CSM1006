#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include <vector>
// Reuse the CSR conversion helper (generateCSR / CSRData) built in
// Assignment_01, Task_03. Per the Assignment_04 instructions we call the
// existing CSR conversion function rather than copy it into this
// assignment. Vertex Coloring is unweighted, so edge weights supplied to
// generateCSR() are simply ignored (the driver passes 0 as a placeholder).
#include "../../../Assignment_01/Task_03/source/csr.h"

struct ColoringResult {
    std::vector<int> colors; // colors[v] = color assigned to vertex v
    int numColors = 0;
};

// Runs greedy vertex coloring using Welsh-Powell ordering (vertices
// processed in non-increasing degree order; each vertex gets the smallest
// color index not already used by an already-colored neighbour), per
// section 2.1.1 of the spec. Operates directly on the CSR representation.
ColoringResult runVertexColoring(const CSRData& csr, int V);

#endif
