#include <bits/stdc++.h>
using namespace std;

// Using Kruskal's Algorithm
// for each edge we check if excluding it disconnects the baseline MST (minimum possible MST that we created) if it does + including it gives the weight of MST same as baseline MST then its critical edge else it's not
// O(m² α(n)) or O(m^2) - time complexity, O(m + n) - space complexity, where m is the number of edges - on each edge we're doing the mstWeight function which is O(m α(n))
class DSU {
    public:
        int components;
        vector<int> parent, _rank;
        
        DSU (int n) : parent(n), _rank(n, 1), components(n) {
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
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
            --components;
            
            return true;
        }
};

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();

        for (int i = 0; i < m; i++) {
            edges[i].push_back(i); // remembering the original indices
        }

        sort(edges.begin(), edges.end(), [](auto &a, auto &b) { // sorting based on weight
            return a[2] < b[2];
        });

        auto mstWeight = [&](int skip, int forceInclude) {
            DSU dsu(n);
            int weight = 0;
            if (forceInclude != -1) {
                dsu.unite(edges[forceInclude][0], edges[forceInclude][1]);
                weight += edges[forceInclude][2];
            }
            for (int i = 0; i < m; i++) {
                if (i == skip || i == forceInclude) continue;
                if (dsu.unite(edges[i][0], edges[i][1])) {
                    weight += edges[i][2];
                }
            }

            return dsu.components == 1 ? weight : INT_MAX;
        };

        vector<vector<int>> result(2);

        int baseline = mstWeight(-1, -1); // minimum possible
        for (int i = 0; i < m; i++) {
            int originalIndex = edges[i][3];

            // excluding edge 'i'
            int exclude = mstWeight(i, -1);
            if (exclude > baseline) {
                result[0].push_back(originalIndex);
                continue;
            }

            // including edge 'i'
            int include = mstWeight(-1, i);
            if (include == baseline) {
                result[1].push_back(originalIndex);
            }
        }

        return result;
    }
};

// Using dijkstra
// From each edge connecting u to v with weight 'w' we ask is there any other edge that connects the same edges but with weights <= w. If there is then if that edge's weight is less than 'w' its critical, if equal to 'w' its pseudo-critical. Hence, we're minimizing the maximum edge weight along with that path -> minimax helper function (modified dijkstra)
// O(m^2log(n)), O(V + E) where m are number of edges, n are number of vertices
class Solution2 {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        for (int i = 0; i < m; i++) {
            edges[i].push_back(i);
        }

        vector<vector<vector<int>>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2], edge[3]});
            adj[edge[1]].push_back({edge[0], edge[2], edge[3]});
        }

        auto minimax = [&] (int source, int destination, int excludeIndex) -> int {
            vector<int> distance(n, INT_MAX);
            distance[source] = 0;

            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
            pq.push({0, source});

            while (!pq.empty()) {
                auto [maxWeight, u] = pq.top();
                pq.pop();

                if (u == destination) return maxWeight;

                for (const auto& neighbor : adj[u]) {
                    int v = neighbor[0], weight = neighbor[1], edgeIndex = neighbor[2];
                    if (edgeIndex == excludeIndex) continue;
                    int newWeight = max(maxWeight, weight);
                    if (newWeight < distance[v]) {
                        distance[v] = newWeight;
                        pq.push({newWeight, v});
                    }
                }
            }
            return INT_MAX;
        };

        vector<vector<int>> result(2);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2], index = edge[3];
            int minmaxWeight = minimax(u, v, index);
            if (w < minmaxWeight) {
                result[0].push_back(index);
            } else if (w == minmaxWeight) {
                result[1].push_back(index);
            }
        }

        return result;
    }
};

// Kruskal + DFS
// after building one MST (baseline), edges not in the MST create cycles when added. So we use DFS to find the path in MST between endpoints of each non MST edges. If any edge on this path has same weight as non-MST edge then both are pseduo critical edges (both can be swapped). Edges that are not identified as pseudo critical would be critical edges.
// Since MST is tree, adding new edge would create exactly one cycle from path u-v where u-v is that extra edge we add. Now when we check using DFS this path again covering (extra + original path from u-v (without cycles)) we check is there any node that is greater than extra edge that we added if yes we can swap that with this edge means these two are swappable (pseudo critical) and all those which couldn't be replaced are critical.
// O(m² α(n)) or O(m^2) - time complexity, O(m + n) - space complexity
class Solution3 {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        for (int i = 0; i < m; i++) { // remember original indices
            edges[i].push_back(i);
        }

        sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });

        // build MST, and adjacency list of MST edges: adj[u] = {(v, weight, originalEdgeIdx)}
        vector<vector<array<int, 3>>> adj(n);
        vector<bool> inMST(m, false);

        DSU dsu(n);
        for (int i = 0; i < m; i++) {
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];
            if (dsu.unite(u, v)) {
                adj[u].push_back({v, w, i});
                adj[v].push_back({u, w, i});
                inMST[i] = true;
            }
        }

        vector<bool> pseudo(m, false);
        // for each non-MST edge, find the tree path between its endpoints via DFS
        for (int i = 0; i < m; i++) {
            if (inMST[i]) continue;
            int u = edges[i][0], v = edges[i][1], w = edges[i][2];

            // DFS from u to v, tracking edges on the path
            vector<int> path; // tracking edges on the path
            vector<bool> visited(n, false);

            function<bool(int)> dfs = [&](int node) -> bool {
                if (node == v) return true;
                visited[node] = true;
                for (auto& [next, weight, edgeIndex] : adj[node]) {
                    if (visited[next]) continue;
                    path.push_back(edgeIndex);
                    if (dfs(next)) return true;
                    path.pop_back();
                }

                return false;
            };

            dfs(u);

            // if any edge on the path has equal weight, both are swappable -> pseudo-critical
            for (int edgeIndex : path) {
                if (edges[edgeIndex][2] == w) {
                    pseudo[edgeIndex] = true;
                    pseudo[i] = true;
                }
            }
        }

        vector<int> critical, pseudoCritical;
        for (int i = 0; i < m; i++) {
            int originalIndex = edges[i][3];
            if (inMST[i] && !pseudo[i]) critical.push_back(originalIndex);
            else if (pseudo[i]) pseudoCritical.push_back(originalIndex);
        }

        return {critical, pseudoCritical};
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
