/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// approach - union-find --> if any edge, connect two nodes in the same set -> cycle. After processing all edges, check if there's exactly one connected component
/*
conditions for graph to be tree :- 
(1) every node is connected and can be reached from some other node
(2) No cycles 
(3) n nodes -> exactly n-1 edges (if more than n - 1 then it would have cycles, if less than n - 1 then it wouldn't be connected graph)
tree = connected acyclic graph
*/

class DSU {
    public: 
        vector<int> parent, rank_;
        DSU(int n) {
            parent.resize(n);
            rank_.assign(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find (int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }

        void unite(int x, int y) {
            int parentX = find(x), parentY = find(y);
            if (parentX == parentY) return;

            if (rank_[parentX] < rank_[parentY]) swap(parentX, parentY);
            parent[parentY] = parentX;
            if (rank_[parentX] == rank_[parentY]) rank_[parentX]++;
        }

        bool hasCycle(int u, int v) {
            int parentU = find(u), parentV = find(v);
            if (parentU == parentV) return true;
            unite(parentU, parentV);
            return false;
        }
};

// using dfs - O(V + E), O(V + E)
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    bool dfs(int node, int parent) {
        if (visited[node]) return false;

        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (neighbor == parent) {
                continue;
            }
            if (!dfs(neighbor, node)) {
                return false;
            }
        }

        return true;
    }

public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) {
            return false;
        }

        adj.resize(n);
        visited.assign(n, false);

        for (auto edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        if (!dfs(0, -1)) {
            return false;
        }

        // checking if all nodes got visited
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                flag = false;
                break;
            }
        }

        return flag;
    }
};

// using bfs - O(V + E), O(V + E)
class Solution2 {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) return false;

        vector<bool> visited(n, false);
        vector<vector<int>> adj(n);

        for (auto edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        queue<pair<int, int>> q;
        q.push({0, -1});
        visited[0] = true;

        while (!q.empty()) {
            auto [node, parent] = q.front(); q.pop();
            for (int neighbor : adj[node]) {
                if (neighbor == parent) continue;
                if (visited[neighbor]) return false;
                visited[neighbor] = true;
                q.push({neighbor, node});
            }
        }

        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                flag = false;
                break;
            }
        }

        return flag;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int V, E; cin >> V >> E;
        DSU dsu(V);
        bool isTree = true;
        for (int i = 0; i < E; i++) {
            int u, v; cin >> u >> v;
            if (dsu.hasCycle(u, v))
                isTree = false;
        } 

        if (E != V - 1) isTree = false;

        cout << isTree << '\n';
    }

    return 0;
}
