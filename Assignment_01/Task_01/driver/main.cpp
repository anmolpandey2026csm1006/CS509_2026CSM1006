#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include <vector>
#include "../source/matrix.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: main <inputFile> <outputFile>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin || !fout) {
        cout << "Error opening files!\n";
        return 1;
    }

    // Read M, K, N based on GEMM input format[cite: 1]
    int M, K, N;
    fin >> M >> K >> N;

    vector<vector<int>> A(M, vector<int>(K));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < K; ++j) {
            fin >> A[i][j];
        }
    }

    vector<vector<int>> B(K, vector<int>(N));
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            fin >> B[i][j];
        }
    }

    auto start = high_resolution_clock::now();
    vector<vector<int>> C = runSimpleGEMM(A, B);
    auto stop = high_resolution_clock::now();

    double execTime = duration<double, milli>(stop - start).count();

    fout << "Algorithm: GEMM Simple\nResult matrix:\n";
    for (const auto& row : C) {
        for (int val : row) {
            fout << val << " ";
        }
        fout << "\n";
    }
    
    // Timing strictly measures algorithm execution[cite: 1]
    fout << "Execution time: " << execTime << " ms\n";

    fin.close();
    fout.close();
    return 0;
}