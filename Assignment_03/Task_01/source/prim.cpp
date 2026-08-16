#include "prim.h"
#include <queue>
#include <vector>
#include <limits>

MSTResult runPrim(const CSRData& csr, int V, int startVertex) {
    MSTResult result;
    if (V == 0) return result;

    const long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> key(V, INF);   // cheapest edge weight connecting v to the tree
    std::vector<int> parent(V, -1);       // other endpoint of that cheapest edge
    std::vector<bool> inMST(V, false);

    // Min-heap of (key, vertex).
    using PLI = std::pair<long long, int>;
    std::priority_queue<PLI, std::vector<PLI>, std::greater<PLI>> pq;

    key[startVertex] = 0;
    pq.push({0, startVertex});

    result.edges.reserve(V > 0 ? V - 1 : 0);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;

        if (parent[u] != -1) {
            result.edges.push_back({parent[u], u, static_cast<int>(key[u])});
            result.totalWeight += key[u];
        }

        for (int idx = csr.row_ptr[u]; idx < csr.row_ptr[u + 1]; ++idx) {
            int v = csr.col_idx[idx];
            int w = csr.values[idx];
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    return result;
}
