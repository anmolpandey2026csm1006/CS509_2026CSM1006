#include "vertexColoring.h"
#include <algorithm>
#include <numeric>

ColoringResult runVertexColoring(const CSRData& csr, int V) {
    ColoringResult result;
    result.colors.assign(V, -1);
    if (V == 0) return result;

    // Order vertices by non-increasing degree (Welsh-Powell heuristic).
    std::vector<int> order(V);
    std::iota(order.begin(), order.end(), 0);
    std::vector<int> degree(V);
    for (int v = 0; v < V; ++v) {
        degree[v] = csr.row_ptr[v + 1] - csr.row_ptr[v];
    }
    std::sort(order.begin(), order.end(),
              [&](int a, int b) { return degree[a] > degree[b]; });

    // Process vertices in that order; assign each the smallest color index
    // not already used by an already-colored neighbour.
    std::vector<char> usedByNeighbour; // reused scratch buffer per vertex
    for (int u : order) {
        int deg = csr.row_ptr[u + 1] - csr.row_ptr[u];
        usedByNeighbour.assign(deg + 1, 0); // at most deg neighbours can
                                             // force colors 0..deg-1 to be
                                             // taken, so color deg is
                                             // always free
        for (int idx = csr.row_ptr[u]; idx < csr.row_ptr[u + 1]; ++idx) {
            int nbr = csr.col_idx[idx];
            int c = result.colors[nbr];
            if (c >= 0 && c <= deg) {
                usedByNeighbour[c] = 1;
            }
        }
        int chosen = 0;
        while (chosen <= deg && usedByNeighbour[chosen]) ++chosen;
        result.colors[u] = chosen;
        result.numColors = std::max(result.numColors, chosen + 1);
    }

    return result;
}
