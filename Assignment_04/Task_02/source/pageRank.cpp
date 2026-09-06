#include "pageRank.h"
#include <cmath>

PageRankResult runPageRank(const CSRData& csr, int V, double damping,
                            double tolerance, long long maxIterations) {
    PageRankResult result;
    if (V == 0) return result;

    std::vector<int> outdeg(V);
    for (int u = 0; u < V; ++u) {
        outdeg[u] = csr.row_ptr[u + 1] - csr.row_ptr[u];
    }

    std::vector<double> rank(V, 1.0 / V);
    std::vector<double> newRank(V);

    long long iter = 0;
    bool converged = false;

    while (iter < maxIterations) {
        double base = (1.0 - damping) / V;
        std::fill(newRank.begin(), newRank.end(), base);

        // Dangling vertices (outdegree 0): redistribute their rank evenly
        // across all vertices, per section 2.2, rather than letting it
        // vanish from the system.
        double danglingSum = 0.0;
        for (int u = 0; u < V; ++u) {
            if (outdeg[u] == 0) danglingSum += rank[u];
        }
        double danglingShare = damping * danglingSum / V;
        for (int v = 0; v < V; ++v) {
            newRank[v] += danglingShare;
        }

        // Standard contribution: PR(u)/outdeg(u) flows to every out-neighbour of u.
        for (int u = 0; u < V; ++u) {
            if (outdeg[u] == 0) continue;
            double contrib = damping * rank[u] / outdeg[u];
            for (int idx = csr.row_ptr[u]; idx < csr.row_ptr[u + 1]; ++idx) {
                int v = csr.col_idx[idx];
                newRank[v] += contrib;
            }
        }

        double totalChange = 0.0;
        for (int v = 0; v < V; ++v) {
            totalChange += std::fabs(newRank[v] - rank[v]);
        }

        rank.swap(newRank);
        ++iter;

        if (totalChange <= tolerance) {
            converged = true;
            break;
        }
    }

    result.ranks = rank;
    result.iterations = iter;
    result.converged = converged;
    return result;
}
