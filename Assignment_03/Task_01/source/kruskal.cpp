#include "kruskal.h"
#include <algorithm>
#include <numeric>

namespace {

// Disjoint Set Union (Union-Find) with path compression and union by rank,
// used internally by Kruskal to detect cycles.
struct DSU {
    std::vector<int> parent, rank_;
    explicit DSU(int n) : parent(n), rank_(n, 0) {
        std::iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // path compression (halving)
            x = parent[x];
        }
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) std::swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};

} // namespace

MSTResult runKruskal(const CSRData& csr, int V) {
    MSTResult result;

    // Extract each undirected edge exactly once from the CSR structure:
    // since every undirected edge appears in both endpoints' adjacency
    // lists with the same weight, only keep the copy seen from the
    // lower-indexed vertex (u < v). This extraction is intentionally
    // performed here (inside the timed algorithm call), per section 8.
    std::vector<MSTEdge> edges;
    edges.reserve(csr.col_idx.size() / 2);
    for (int u = 0; u < V; ++u) {
        for (int idx = csr.row_ptr[u]; idx < csr.row_ptr[u + 1]; ++idx) {
            int v = csr.col_idx[idx];
            if (v > u) {
                edges.push_back({u, v, csr.values[idx]});
            }
        }
    }

    std::sort(edges.begin(), edges.end(),
              [](const MSTEdge& a, const MSTEdge& b) { return a.weight < b.weight; });

    DSU dsu(V);
    result.edges.reserve(V > 0 ? V - 1 : 0);
    for (const auto& e : edges) {
        if (static_cast<int>(result.edges.size()) == V - 1) break; // MST complete
        if (dsu.unite(e.u, e.v)) {
            result.edges.push_back(e);
            result.totalWeight += e.weight;
        }
    }

    return result;
}
