#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include "../source/kruskal.h"
#include "../source/prim.h"

using namespace std;
using namespace chrono;

static void printMSTResult(ostream& out, const string& algoName, const MSTResult& result, double execTime) {
    out << "Algorithm: " << algoName << "\n";
    out << "MST edges:\n";
    for (const auto& e : result.edges) {
        out << e.u << " " << e.v << " " << e.weight << "\n";
    }
    out << "Total MST weight: " << result.totalWeight << "\n";
    out << "Execution time: " << execTime << " ms\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: mstMain <inputFile> <outputFile>\n";
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
    //   u0 degree n1 w1 n2 w2 ...
    int V, E;
    if (!(fin >> V >> E) || V <= 0) {
        cout << "Error: invalid or missing 'V E' header in '" << argv[1] << "'\n";
        return 1;
    }

    vector<vector<pair<int, int>>> adjList(V);
    for (int i = 0; i < V; ++i) {
        int u, degree;
        if (!(fin >> u >> degree) || u < 0 || u >= V) {
            cout << "Error: invalid/truncated adjacency line " << i
                 << " in '" << argv[1] << "'\n";
            return 1;
        }
        adjList[u].reserve(degree);
        for (int k = 0; k < degree; ++k) {
            int nbr, w;
            if (!(fin >> nbr >> w)) {
                cout << "Error: truncated neighbour/weight list for vertex "
                     << u << " in '" << argv[1] << "'\n";
                return 1;
            }
            adjList[u].push_back({nbr, w});
        }
    }

    if (V > 1) {
        bool anyEdges = false;
        for (const auto& nbrs : adjList) {
            if (!nbrs.empty()) { anyEdges = true; break; }
        }
        if (!anyEdges) {
            cout << "Error: MST input with V > 1 cannot have every vertex isolated in '"
                 << argv[1] << "'\n";
            return 1;
        }
    }

    // Preprocessing (NOT timed): adjacency list -> CSR, via generateCSR()
    // reused from Assignment_01 / Task_03.
    CSRData csr = generateCSR(V, adjList);

    // Timed region 1: Kruskal (edge extraction + sort happens inside it).
    auto k0 = high_resolution_clock::now();
    MSTResult kruskalResult = runKruskal(csr, V);
    auto k1 = high_resolution_clock::now();
    double kruskalTime = duration<double, milli>(k1 - k0).count();

    // Timed region 2: Prim.
    auto p0 = high_resolution_clock::now();
    MSTResult primResult = runPrim(csr, V, 0);
    auto p1 = high_resolution_clock::now();
    double primTime = duration<double, milli>(p1 - p0).count();

    if (static_cast<int>(kruskalResult.edges.size()) != V - 1 ||
        static_cast<int>(primResult.edges.size()) != V - 1) {
        fout << "WARNING: graph appears to be disconnected - Kruskal found "
             << kruskalResult.edges.size() << " edges and Prim found "
             << primResult.edges.size() << " edges, expected " << (V - 1)
             << " for a valid spanning tree.\n\n";
    }

    printMSTResult(fout, "Kruskal's MST", kruskalResult, kruskalTime);
    fout << "\n";
    printMSTResult(fout, "Prim's MST", primResult, primTime);

    fin.close();
    fout.close();
    return 0;
}
