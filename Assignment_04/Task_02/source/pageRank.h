#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include <vector>
// Reuse the CSR conversion helper (generateCSR / CSRData) built in
// Assignment_01, Task_03. Per the Assignment_04 instructions we call the
// existing CSR conversion function rather than copy it into this
// assignment. PageRank is unweighted, so edge weights supplied to
// generateCSR() are simply ignored (the driver passes 0 as a placeholder).
#include "../../../Assignment_01/Task_03/source/csr.h"

struct PageRankResult {
    std::vector<double> ranks;
    long long iterations = 0;
    bool converged = false;
};

// Runs PageRank on a directed, unweighted CSR graph (row_ptr/col_idx hold
// out-edges: csr.col_idx[idx] for idx in [row_ptr[u], row_ptr[u+1]) are
// u's out-neighbours). A dangling vertex (outdegree 0) has its rank
// redistributed evenly across all vertices each iteration, per section
// 2.2. All iterations of the update loop are part of the timed region,
// per section 9.
PageRankResult runPageRank(const CSRData& csr, int V, double damping,
                            double tolerance, long long maxIterations);

#endif
