/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool hasCycle(int V, const vector<vector<int>>& adj) {
    vector<int> state(V, 0); // 0 = unvisited, 1 = in progress (on current DFS path), 2 = done
    for (int start = 0; start < V; start++) {
        if (state[start] != 0) continue;
        stack<pair<int,int>> st; // {node, index of next neighbor to process}
        st.push({start, 0});
        state[start] = 1;
        while (!st.empty()) {
            auto& [node, idx] = st.top(); // reference: modifying idx updates the stack frame
            if (idx < (int)adj[node].size()) {
                int neighbor = adj[node][idx];
                idx++; // advance pointer so we resume correctly next time this frame is on top
                if (state[neighbor] == 1) {
                    return true; // back edge to a node on current path -> cycle
                }
                if (state[neighbor] == 0) {
                    state[neighbor] = 1;
                    st.push({neighbor, 0});
                }
                // if state[neighbor] == 2, already fully processed, safe to skip
            } else {
                state[node] = 2; // fully processed, backtrack
                st.pop();
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long t; cin >> t;
    while (t--) {
        int V, E; cin >> V >> E;
        vector<vector<int>> adj(V);
        for (int i = 0; i < E; i++) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
        }

        cout << hasCycle(V, adj) << '\n';
    }
    return 0;
}
