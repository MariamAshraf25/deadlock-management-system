/*
Project Name: Deadlock Management System
Author:       Mariam Ashraf
Major:        Computer Engineering
Date:         May 2025
Description:  A C++ command-line tool designed to handle Operating System deadlocks. 
              It includes two primary modules: 
              1. Deadlock Avoidance using the Banker's Algorithm to find safe execution sequences.
              2. Deadlock Detection using Resource Allocation Graphs (RAG) and Wait-For Graphs (WFG).
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ========== RESOURCE ALLOCATION GRAPH + WAIT FOR GRAPH ==========
void drawResourceAndWaitForGraph() {
    int processes = 5;
    int resources = 5;

    // Hardcoded Allocation Matrix
    vector<vector<int>> allocation = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0}
    };

    // Hardcoded Request Matrix
    vector<vector<int>> request = {
        {1, 0, 0, 0, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    cout << "\n--- Resource Allocation Graph ---\n";
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            if (allocation[i][j] > 0)
                cout << "R" << (j + 1) << " -> P" << (i + 1) << "\n";
            if (request[i][j] > 0)
                cout << "P" << (i + 1) << " -> R" << (j + 1) << "\n";
        }
    }

    cout << "\n--- Wait-for Graph ---\n";
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            if (request[i][j] > 0) {
                for (int k = 0; k < processes; ++k) {
                    if (allocation[k][j] > 0)
                        cout << "P" << (i + 1) << " -> P" << (k + 1) << "\n";
                }
            }
        }
    }
}

// ========== BANKER'S ALGORITHM ==========
void bankersAlgorithm() {
    int n, m;
    cout << "Enter number of processes and resource types: ";
    cin >> n >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> allocation[i][j];

    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            cin >> max[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }

    cout << "Enter Available Resources:\n";
    for (int i = 0; i < m; ++i)
        cin >> available[i];

    vector<bool> finish(n, false);
    vector<int> safeSequence;
    for (int count = 0; count < n; ++count) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; ++j)
                        available[j] += allocation[i][j];
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                    break;
                }
            }
        }
        if (!found) break;
    }

    if (safeSequence.size() == n) {
        cout << "\nSystem is in a safe state.\nSafe sequence: ";
        for (int p : safeSequence)
            cout << "P" << (p ) << " ";//no...
        cout << endl;
    }
    else {
        cout << "\nSystem is NOT in a safe state (Deadlock Possible).\n";
    }
}

// ========== MAIN MENU ==========
int main() {
    while (true) {
        int choice;
        cout << "\n===== DEADLOCK MENU =====\n";
        cout << "1. Draw Resource & Wait-for Graphs\n";
        cout << "2. Banker's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:
            drawResourceAndWaitForGraph();
            break;
        case 2:
            bankersAlgorithm();
            break;
        case 3:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
