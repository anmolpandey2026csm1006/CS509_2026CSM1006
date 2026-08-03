#include "csr.h"
#include<bits/stdc++.h>

using namespace std;

CSRData generateCSR(int V, const vector<vector<pair<int, int>>>& adjList) {
    CSRData csr;
    csr.row_ptr.push_back(0); 
    
    for (int i = 0; i < V; ++i) {
        for (const auto& neighbor : adjList[i]) {
            csr.col_idx.push_back(neighbor.first);
            csr.values.push_back(neighbor.second);
        }
        // The row pointer tracks where the next vertex's neighbors begin
        csr.row_ptr.push_back(csr.col_idx.size()); 
    }
    
    return csr;
}