#include <bits/stdc++.h>
using namespace std;

// Brute force DFS : tree doesn't contains any cycles so we keep adding edges and dfs after adding each edge then we check that whether on adding this node made the graph have a cycle - first edge that does this is the required answer. Since there is only single edge that would make the graph make a cycle, the case where problems asks for printing the last edge in the input when there are multiple answers is handled as well (first = last). O(E*(V + E)), O(V + E)
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    bool dfs(int node, int parent) {
        if (visited[node]) {
            return true;
        }
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            if (dfs(neighbor, node)) return true;
        }

        return false;
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        adj.resize(n + 1);

        for (auto edge : edges) {
            int u = edge[0], v = edge[1];
            visited.assign(n + 1, false);

            adj[u].push_back(v);
            adj[v].push_back(u);

            if (dfs(u, -1)) {
                return {u, v};
            }
        }

        return {};
    }
};

// DFS (Optimal) :  Since there is only single cycle in the given graph, build the graph and find the cycle using single dfs and mark all the nodes that led to the start of the cycle - now we have all the nodes present in the cycle. To get the edge that makes this cycle and present last in the input just traverse the edges from the end and find edge (u, v) such that both the vertices are present in cycle nodes. O(V + E), O(V + E)
class Solution2 {
private:
    vector<vector<int>> adj;
    vector<bool> visited;
    unordered_set<int> cycle_nodes;

    int cycleStart;

    bool dfs(int node, int parent) {
        if (visited[node]) {
            cycleStart = node;
            return true;
        }

        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            if (dfs(neighbor, node)) {
                if (cycleStart != -1) {
                    cycle_nodes.insert(node);
                }
                if (node == cycleStart) { // once we reach back to the node again reset cycleStart so above the tree, nodes that are not part of the cycles don't get added
                    cycleStart = -1;
                }
                return true;
            }
        }

        return false;
    }

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        adj.resize(n + 1);
        visited.assign(n + 1, false);

        for (auto edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        cycleStart = -1;
        dfs(edges[0][0], -1);

        for (int i = n - 1; i >= 0; i--) {
            int u = edges[i][0], v = edges[i][1];

            if (cycle_nodes.count(u) && cycle_nodes.count(v)) {
                return {u, v};
            }
        }

        return {};
    }
};

// Topological Sort (Kahn's) : Using "peel off leaves" (often called topological trimming) - the nodes which are in the cycle they wouldn't have degree = 1. So we push all the nodes whose degree is 1 (this is undirected graph NOT directed graph so indegree, degree same things). We push all nodes with degree = 1 in a queue and remove them and their children might also become leaf since there degree would also decrease, so we check and push those as well. In the end we would only have nodes whose degree > 0 -> cycle nodes. Again just traverse edges from the end - edge whose both vertices match with these nodes is the required answer. O(V + E), O(V + E)
class Solution3 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        vector<vector<int>> adj(n + 1);
        vector<int> inDegree(n + 1, 0);

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            inDegree[u]++; inDegree[v]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (inDegree[i] == 1) q.push(i);
        }

        while (!q.empty()) {
            int node = q.front(); q.pop();
            inDegree[node]--;
            for (int neighbor : adj[node]) {
                if (--inDegree[neighbor] == 1) q.push(neighbor);
            }
        }

        for (int i = edges.size() - 1; i >= 0; i--) {
            int u = edges[i][0], v = edges[i][1];
            if (inDegree[u] == 2 && inDegree[v] == 2) {
                return {u, v};
            }
        }

        return {};
    }
};

// Using Union Find (DSUs) : Just adding the edges and connecting them in order. First edge that is already connected but we're trying to merge is the one that creates cycle. Since we're processing edges in order, first edge that fails this union is the required answer. O(V+(E∗α(V))) + O(V)
class DSU {
    public:
        vector<int> parent, _rank;

        DSU (int n) {
            _rank.assign(n, 0);
            parent.resize(n);
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        bool unite(int x, int y) {
            int rootX = find(x), rootY = find(y);
            
            if (rootX == rootY) return false;

            if (_rank[rootX] < _rank[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            if (_rank[rootX] == _rank[rootY]) _rank[rootX]++;

            return true;
        }
};
class Solution4 {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        DSU dsu(n + 1);

        for (auto& edge : edges) {
            if (!dsu.unite(edge[0], edge[1])) {
                return { edge[0], edge[1] };
            }
        }

        return {};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
