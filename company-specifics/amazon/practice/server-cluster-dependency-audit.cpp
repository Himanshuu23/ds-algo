#include <bits/stdc++.h>
using namespace std;

/*
Amazon's internal network has n servers labeled 0 to n-1, connected by m directed communication links edges[i] = [u, v] meaning server u can send a signal to server v.
A monitoring probe is placed at server 0. Return the list of all server IDs that are reachable from server 0, in ascending order.
Additionally, the network security team wants to know if there exists any cycle reachable from server 0 (a signal that can eventually loop back to a server it already passed through). Return this as a boolean along with the reachable list.
Output format: pair<vector<int>, bool> — (reachable servers sorted ascending, cycle_exists_in_reachable_region)
Constraints
1 ≤ n ≤ 10^5
0 ≤ m ≤ 2×10^5
0 ≤ u, v < n, self-loops possible
Example
n = 6, edges = [[0,1],[1,2],[2,0],[0,3],[3,4]]
Output: reachable = [0,1,2,3,4], cycle_exists = true
(0→1→2→0 is a cycle; server 5 is unreachable so it's excluded and irrelevant to the cycle check.)
*/

// cycle detection in directed graph - but for single node
// O(V + E)
bool hasCycle = false;
void dfs(int node, vector<vector<int>>& adj, vector<int>& state) {
    state[node] = 1; // currently being processed
    for (int neighbour : adj[node]) {
        if (state[neighbour] == 1) { // reached again
            hasCycle = true;
        } else if (state[neighbour] == 0) { // not visited
            dfs(neighbour, adj, state);
        }
    }

    state[node] = 2; // full processed
}

pair<vector<int>, bool> solve(int n, int m, vector<vector<int>>& adj) {
    vector<int> state(n, 0);
    dfs(0, adj, state);

    vector<int> reachable;
    for (int i = 0; i < n; i++) {
        if (state[i] != 0) {
            reachable.push_back(i);
        }
    }

    return { reachable, hasCycle };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        hasCycle = false; // resetting for each testcase

        int n, m; cin >> n >> m;
        vector<vector<int>> adj(n);
        
        for (int i = 0; i < m; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
        }

        pair<vector<int>, bool> p = solve(n, m, adj);
        for (int x : p.first) {
            cout << x << " ";
        }
        cout << '\n';
        cout << "has cycle " << p.second << '\n';
    }

    return 0;
}
