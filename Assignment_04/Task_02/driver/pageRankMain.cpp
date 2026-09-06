#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
#include "../source/pageRank.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: pageRankMain <inputFile> <outputFile>\n";
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

    // Section 6.1 format:
    //   V E
    //   u0 outdegree n1 n2 ...
    //   ...
    //   DAMPING d
    //   TOLERANCE epsilon
    //   MAX_ITERATIONS n
    int V, E;
    if (!(fin >> V >> E) || V <= 0) {
        cout << "Error: invalid or missing 'V E' header in '" << argv[1] << "'\n";
        return 1;
    }

    vector<vector<pair<int, int>>> adjList(V); // weight is an unused placeholder (0)
    for (int i = 0; i < V; ++i) {
        int u, outdeg;
        if (!(fin >> u >> outdeg) || u < 0 || u >= V) {
            cout << "Error: invalid/truncated adjacency line " << i
                 << " in '" << argv[1] << "'\n";
            return 1;
        }
        adjList[u].reserve(outdeg);
        for (int k = 0; k < outdeg; ++k) {
            int nbr;
            if (!(fin >> nbr)) {
                cout << "Error: mismatched outdegree/neighbour count for vertex "
                     << u << " in '" << argv[1] << "'\n";
                return 1;
            }
            if (nbr < 0 || nbr >= V) {
                cout << "Error: out-of-range vertex id " << nbr
                     << " in the neighbour list of vertex " << u
                     << " in '" << argv[1] << "'\n";
                return 1;
            }
            adjList[u].push_back({nbr, 0});
        }
    }

    string tag;
    double damping, tolerance;
    long long maxIterations;

    if (!(fin >> tag >> damping) || tag != "DAMPING" || damping <= 0.0 || damping >= 1.0) {
        cout << "Error: missing/invalid 'DAMPING d' (must satisfy 0 < d < 1) in '"
             << argv[1] << "'\n";
        return 1;
    }
    if (!(fin >> tag >> tolerance) || tag != "TOLERANCE" || tolerance <= 0.0) {
        cout << "Error: missing/invalid 'TOLERANCE epsilon' (must be > 0) in '"
             << argv[1] << "'\n";
        return 1;
    }
    if (!(fin >> tag >> maxIterations) || tag != "MAX_ITERATIONS" || maxIterations <= 0) {
        cout << "Error: missing/invalid 'MAX_ITERATIONS n' (must be > 0) in '"
             << argv[1] << "'\n";
        return 1;
    }

    // Preprocessing (NOT timed): adjacency list -> CSR, via generateCSR()
    // reused from Assignment_01 / Task_03.
    CSRData csr = generateCSR(V, adjList);

    // Timed region: all iterations of the rank-update loop, per section 9.
    auto start = high_resolution_clock::now();
    PageRankResult result = runPageRank(csr, V, damping, tolerance, maxIterations);
    auto stop = high_resolution_clock::now();
    double execTime = duration<double, milli>(stop - start).count();

    double sumRanks = 0.0;
    for (double r : result.ranks) sumRanks += r;

    fout << "Algorithm: PageRank\n";
    fout << "Damping: " << damping << "\n";
    fout << "Vertex ranks:\n";
    fout << fixed << setprecision(6);
    for (int v = 0; v < V; ++v) {
        fout << v << " " << result.ranks[v] << "\n";
    }
    fout << "Sum of ranks: " << sumRanks << "\n";
    fout.unsetf(ios::fixed);
    fout << setprecision(6);
    fout << "Iterations: " << result.iterations << "\n";
    fout << "Converged: " << (result.converged ? "true" : "false") << "\n";
    fout << "Execution time: " << execTime << " ms\n";

    fin.close();
    fout.close();
    return 0;
}
