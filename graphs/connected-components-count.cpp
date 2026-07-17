/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
DFS/BFS: O(V + E) — each vertex visited once, each edge examined once (twice total across both directions in an undirected graph, still O(E)).
DSU: O(E · α(V)) for all the unite() calls (one per edge) + O(V · α(V)) for the final find() pass over all vertices ≈ O((V+E) · α(V)), which is practically O(V+E) since α is essentially constant.
in findIslands problem we did O(E) = 4V and did complexity for dsu O(V) here we can't do that because in there we had grid so 
each element could max have 4 neighbours atmost but here that isn't the case.
*/

class DSU {
    vector<int> parent, rank_;
    public:
        DSU(int n) {
           parent.resize(n);
           rank_.assign(n, 0);
           for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x), rootY = find(y);

            if (rootX == rootY) return;
            if (rank_[rootX] < rank_[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            if (rank_[rootX] == rank_[rootY]) rank_[rootX]++;
        }
};

int findConnectedComponentsUsingDSU(vector<vector<int>>& adj) {
    int V = adj.size();
    DSU dsu(V);

    for (int i = 0; i < V; i++) {
        for (int neighbour : adj[i]) {
            dsu.unite(i, neighbour);
        }
    }

    set<int> daddy;
    for (int i = 0; i < V; i++) {
        daddy.insert(dsu.find(i));
    }

    return daddy.size();
}

void dfs(int node, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) dfs(neighbor, adj, visited);
    }
}

int countConnectedComponents(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    int count = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited);
            count++;
        }
    }

    return count;
}

int bfsCountConnectedComponents(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    int count = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }

            count++;
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int V = 6;
        vector<vector<int>> adj(V);

        vector<pair<int, int>> edges = {
            {0, 1}, {1, 2}, {3, 4}
        };

        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int result_dfs = countConnectedComponents(V, adj);
        cout << "DFS: Number of connected components: " << result_dfs << endl;

        int result_bfs = bfsCountConnectedComponents(V, adj);
        cout << "BFS: Number of connected components: " << result_bfs << endl;

        cout << findConnectedComponentsUsingDSU(adj) << 'n';
    }

    return 0;
}
