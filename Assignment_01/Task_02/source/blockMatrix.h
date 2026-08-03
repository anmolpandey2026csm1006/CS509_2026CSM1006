#ifndef BLOCK_MATRIX_H
#define BLOCK_MATRIX_H

#include <vector>

// Function prototype for cache-efficient Blocking GEMM
std::vector<std::vector<int>> executeBlockingGEMM(
    const std::vector<std::vector<int>>& matA, 
    const std::vector<std::vector<int>>& matB, 
    int blockSize);

#endif