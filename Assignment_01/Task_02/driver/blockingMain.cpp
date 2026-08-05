#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include <vector>
#include "../source/blockMatrix.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: blockingMain <inputFile> <outputFile>\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile || !outputFile) {
        cout << "Error: Unable to open the specified files.\n";
        return 1;
    }

    // Parse dimensions: M x K for Matrix A, K x N for Matrix B[cite: 1]
    int M, K, N;
    inputFile >> M >> K >> N;

    vector<vector<int>> A(M, vector<int>(K));
    for (int r = 0; r < M; ++r) {
        for (int c = 0; c < K; ++c) {
            inputFile >> A[r][c];
        }
    }

    vector<vector<int>> B(K, vector<int>(N));
    for (int r = 0; r < K; ++r) {
        for (int c = 0; c < N; ++c) {
            inputFile >> B[r][c];
        }
    }

    int blockSize;
    // Set the block size (or tile size) for cache reuse
    if(K > 128 && M > 128 && N > 128)
        blockSize = 64;
    else
        blockSize = 2; 


    // Start timing ONLY the algorithm execution[cite: 1]
    auto startTime = high_resolution_clock::now();
    
    vector<vector<int>> C = executeBlockingGEMM(A, B, blockSize);
    
    auto stopTime = high_resolution_clock::now();
    double executionTimeMs = duration<double, milli>(stopTime - startTime).count();

    // Write expected output format[cite: 1]
    outputFile << "Algorithm: GEMM Blocking\nResult matrix:\n";
    for (const auto& row : C) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << row[i] << (i == row.size() - 1 ? "" : " ");
        }
        outputFile << "\n";
    }
    
    outputFile << "Execution time: " << executionTimeMs << " ms\n";

    inputFile.close();
    outputFile.close();
    
    return 0;
}