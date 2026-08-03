#ifndef CSR_H
#define CSR_H

#include <vector>
#include <utility>

struct CSRData {
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<int> values;
};

// Function prototype for CSR generation
CSRData generateCSR(int V, const std::vector<std::vector<std::pair<int, int>>>& adjList);

#endif