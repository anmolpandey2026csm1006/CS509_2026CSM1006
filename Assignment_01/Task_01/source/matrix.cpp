#include "matrix.h"
#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> runSimpleGEMM(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int M = A.size();
    int K = A[0].size();
    int N = B[0].size();

    vector<vector<int>> C(M, vector<int>(N, 0));

    // Simple nested loop implementation
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}