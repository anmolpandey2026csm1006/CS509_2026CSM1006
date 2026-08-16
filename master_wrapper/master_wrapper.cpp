#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Function to safely navigate, compile, and execute a sub-wrapper
void launchAssignment(const string& folderName) {
    cout << "\n>>> Transitioning to " << folderName << " Environment <<<\n";
    
    // The command does 3 things:
    // 1. cd into the specific assignment folder
    // 2. Compiles the local common_wrapper.cpp 
    // 3. Executes the resulting wrapper_app
    string cmd = "cd " + folderName + " && g++ common_wrapper.cpp -o wrapper_app && ./wrapper_app";
    
    // Execute the chained command
    system(cmd.c_str());
    
    cout << "\n>>> Returned to Master Environment <<<\n";
}

int main() {
    int mainOpt = -1;

    while (mainOpt != 0) {
        cout << "\n=================================================\n";
        cout << "     CS509 Master Project Manager (Individual)   \n";
        cout << "=================================================\n";
        cout << "1. Open Assignment 01 (Simple/Blocked GEMM, CSR)\n";
        cout << "2. Open Assignment 02 (Bellman-Ford, Floyd-Warshall)\n";
        cout << "3. Open Assignment 03 (MST: Kruskal & Prim)\n";
        cout << "0. Exit Master System\n";
        cout << "\nEnter your choice: ";
        cin >> mainOpt;

        switch (mainOpt) {
            case 1:
                launchAssignment("Assignment_01");
                break;
            case 2:
                launchAssignment("Assignment_02");
                break;
            case 3:
                launchAssignment("Assignment_03");
                break;
            case 0:
                cout << "\nShutting down master environment. Goodbye!\n";
                break;
            default:
                cout << "\nError: Choice not recognized. Please try again.\n";
        }
    }
    return 0;
}