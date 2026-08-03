#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include "../source/csr.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: csrMain <inputFile> <outputFile>\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    ofstream outputFile(argv[2]);

    if (!inputFile || !outputFile) {
        cout << "Error: Unable to open the specified files.\n";
        return 1;
    }

    // Parse V (Vertices) and E (Edges)[cite: 1]
    int V, E;
    inputFile >> V >> E;

    vector<vector<pair<int, int>>> adjList(V);

    // Read unweighted adjacency list[cite: 1]
    for (int i = 0; i < V; ++i) {
        int u, degree;
        inputFile >> u >> degree;
        for (int j = 0; j < degree; ++j) {
            int v;
            inputFile >> v;
            adjList[u].push_back({v, 1}); // Store with a default weight of 1
        }
    }

    // Start timing the CSR conversion (Note: For graph algorithms, this is usually excluded, 
    // but here we are specifically testing the CSR conversion itself)[cite: 1]
    auto startTime = high_resolution_clock::now();
    
    CSRData csr = generateCSR(V, adjList);
    
    auto stopTime = high_resolution_clock::now();
    double executionTimeMs = duration<double, milli>(stopTime - startTime).count();

    // Print CSR arrays to the output file
    outputFile << "--- CSR Representation ---\n";
    
    outputFile << "row_ptr: ";
    for (int val : csr.row_ptr) outputFile << val << " ";
    outputFile << "\n";

    outputFile << "col_idx: ";
    for (int val : csr.col_idx) outputFile << val << " ";
    outputFile << "\n";

    outputFile << "values:  ";
    for (int val : csr.values) outputFile << val << " ";
    outputFile << "\n";

    outputFile << "\nCSR Conversion Time: " << executionTimeMs << " ms\n";

    inputFile.close();
    outputFile.close();
    
    return 0;
}