#include <iostream>
#include <vector>
#include <string>
using namespace std;

class WaitForGraph {
private:
    int numProcesses;
    vector<vector<int>> adj;
    vector<bool> visited, inStack;
    vector<int> parent;
    vector<int> cycle;

    bool dfs(int u) {
        visited[u] = true;
        inStack[u] = true;

        for (int v : adj[u]) {
            if (!visited[v]) {
                parent[v] = u;
                if (dfs(v)) return true;
            } else if (inStack[v]) {
                // cycle found: reconstruct cycle path
                cycle.clear();
                int cur = u;
                cycle.push_back(v);
                while (cur != v) {
                    cycle.push_back(cur);
                    cur = parent[cur];
                }
                cycle.push_back(v); // close the cycle
                return true;
            }
        }

        inStack[u] = false;
        return false;
    }

public:
    WaitForGraph(int n) {
        numProcesses = n;
        adj.resize(n);
        visited.assign(n, false);
        inStack.assign(n, false);
        parent.assign(n, -1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool detectDeadlock() {
        for (int i = 0; i < numProcesses; i++) {
            if (!visited[i]) {
                if (dfs(i)) return true;
            }
        }
        return false;
    }

    void printCycleProcesses() {
        if (cycle.empty()) {
            cout << "\nNo Deadlock detected." << endl;
        } else {
            cout << "\nDeadlock detected involving processes: ";
            for (int i = cycle.size() - 2; i >= 0; i--) { // print cycle once
                cout << "P" << cycle[i] + 1 << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n, e;
    cout << "Enter the number of processes: ";
    cin >> n;

    WaitForGraph wfg(n);

    cout << "Enter the number of edges: ";
    cin >> e;

    cout << "Enter edges (format: P1 -> P2):\n";
    for (int i = 0; i < e; i++) {
        string from, arrow, to;
        cin >> from >> arrow >> to;

        int u = stoi(from.substr(1)) - 1;  // P1 → 0
        int v = stoi(to.substr(1)) - 1;    // P2 → 1

        wfg.addEdge(u, v);
    }

    bool deadlock = wfg.detectDeadlock();
    wfg.printCycleProcesses();

    return 0;
}


