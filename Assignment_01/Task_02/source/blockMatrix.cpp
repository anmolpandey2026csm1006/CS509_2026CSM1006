#include "blockMatrix.h"
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> executeBlockingGEMM(
    const vector<vector<int>>& matA, 
    const vector<vector<int>>& matB, 
    int blockSize) 
{
    int M = matA.size();
    int K = matA[0].size();
    int N = matB[0].size();

    // Initialize the result matrix C with zeros
    vector<vector<int>> C(M, vector<int>(N, 0));

    // Iterate over matrix blocks
    for (int rowBlock = 0; rowBlock < M; rowBlock += blockSize) {
        for (int colBlock = 0; colBlock < N; colBlock += blockSize) {
            for (int innerBlock = 0; innerBlock < K; innerBlock += blockSize) {
                
                // Determine the boundaries to prevent out-of-bounds memory access
                int rMax = min(rowBlock + blockSize, M);
                int cMax = min(colBlock + blockSize, N);
                int iMax = min(innerBlock + blockSize, K);
                
                // Perform standard GEMM inside the current block
                for (int r = rowBlock; r < rMax; ++r) {
                    for (int c = colBlock; c < cMax; ++c) {
                        int blockSum = 0;
                        for (int i = innerBlock; i < iMax; ++i) {
                            blockSum += matA[r][i] * matB[i][c];
                        }
                        C[r][c] += blockSum;
                    }
                }
            }
        }
    }
    return C;
}