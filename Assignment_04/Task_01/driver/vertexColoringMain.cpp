#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include "../source/vertexColoring.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: vertexColoringMain <inputFile> <outputFile>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    if (!fin) {
        cout << "Error: could not open input file '" << argv[1] << "'\n";
        return 1;
    }
    if (!fout) {
        cout << "Error: could not open output file '" << argv[2] << "'\n";
        return 1;
    }

    // Section 5.1 format:
    //   V E
    //   u0 degree n1 n2 ...
    int V, E;
    if (!(fin >> V >> E) || V <= 0) {
        cout << "Error: invalid or missing 'V E' header in '" << argv[1] << "'\n";
        return 1;
    }

    vector<vector<pair<int, int>>> adjList(V); // weight is an unused placeholder (0)
    for (int i = 0; i < V; ++i) {
        int u, degree;
        if (!(fin >> u >> degree) || u < 0 || u >= V) {
            cout << "Error: invalid/truncated adjacency line " << i
                 << " in '" << argv[1] << "'\n";
            return 1;
        }
        adjList[u].reserve(degree);
        for (int k = 0; k < degree; ++k) {
            int nbr;
            if (!(fin >> nbr)) {
                cout << "Error: mismatched degree/neighbour count for vertex "
                     << u << " in '" << argv[1] << "'\n";
                return 1;
            }
            if (nbr < 0 || nbr >= V) {
                cout << "Error: out-of-range vertex id " << nbr
                     << " in the neighbour list of vertex " << u
                     << " in '" << argv[1] << "'\n";
                return 1;
            }
            if (nbr == u) {
                cout << "Error: self-loop at vertex " << u << " in '"
                     << argv[1] << "' - Vertex Coloring graphs must not "
                        "contain self-loops\n";
                return 1;
            }
            adjList[u].push_back({nbr, 0});
        }
    }

    // Preprocessing (NOT timed): adjacency list -> CSR, via generateCSR()
    // reused from Assignment_01 / Task_03.
    CSRData csr = generateCSR(V, adjList);

    // Timed region: algorithm only.
    auto start = high_resolution_clock::now();
    ColoringResult result = runVertexColoring(csr, V);
    auto stop = high_resolution_clock::now();
    double execTime = duration<double, milli>(stop - start).count();

    // Correctness check (NOT timed - a post-hoc verification pass, not
    // part of the coloring algorithm itself, per section 2.1).
    bool valid = true;
    for (int u = 0; u < V && valid; ++u) {
        for (int idx = csr.row_ptr[u]; idx < csr.row_ptr[u + 1]; ++idx) {
            int v = csr.col_idx[idx];
            if (result.colors[u] == result.colors[v]) {
                valid = false;
                break;
            }
        }
    }

    fout << "Algorithm: Greedy Vertex Coloring\n";
    fout << "Vertex colors:\n";
    for (int v = 0; v < V; ++v) {
        fout << v << " " << result.colors[v] << "\n";
    }
    fout << "Colors used: " << result.numColors << "\n";
    fout << "Valid coloring: " << (valid ? "true" : "false") << "\n";
    fout << "Execution time: " << execTime << " ms\n";

    fin.close();
    fout.close();
    return 0;
}
