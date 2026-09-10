#include <bits/stdc++.h>
using namespace std;

// we can think of each equation as directed graph from 'a' -> 'b' with weight of value hence query (a, b) represents path from a/b and as we move through that path we multiply each weight. And also if a->b weight is value, b->a weight is 1/value. If some node doesn't exist from the query or path doesn't leads to the target -> -1.0

// Using BFS - since we want explore the neighbors first, then go further
// O(m * n) where m are number of query, n are number of unique strings -> total nodes that we would be making and hence bfs on each query. O(m + n)
// another optimization: adding cache(source, target) : answer, and good part is if we know answer from (a, b) then we also know answer from (b, a) and also we can stop immediately avoiding not existing paths that give -1.0 and also same paths recalculations is avoiding and hence improving the overall performance - for overall queries
class Solution {
private:
    unordered_map<string, vector<pair<string, double>>> adj; // map of 'a' -> ['b', a/b] child and its weight 
    unordered_map<string, unordered_map<string, double>> cache; 
    unordered_set<string> visited;


    double bfs(const string& source, const string& target) {
        if (!adj.count(source) || !adj.count(target)) {
            return -1.0;
        }

        auto it = cache.find(source);
        if (it != cache.end()) {
            auto jt = it->second.find(target);
            if (jt != it->second.end()) return jt->second;
        }

        queue<pair<string, double>> q;
        q.push({ source, 1.0 });
        visited.insert(source);

        while (!q.empty()) {
            auto [node, weight] = q.front(); q.pop();

            cache[source][node] = weight;
            cache[node][source] = 1 / weight;

            if (node == target) {
                return weight;
            }


            for (const auto& [neighbor, neighbor_weight] : adj[node]) {
                if (!visited.count(neighbor)) {
                    q.push({ neighbor, weight * neighbor_weight });
                    visited.insert(neighbor);
                }
            }
        }

        cache[source][target] = -1.0;
        return -1.0;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // building the graph
        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];

            adj[a].emplace_back(b, values[i]);
            adj[b].emplace_back(a, 1.0 / values[i]);
        } 

        vector<double> result;
        for (const auto& query : queries) {
            string source = query[0];
            string target = query[1];
            visited.clear();
            result.push_back(bfs(source, target));
        }

        return result;
    }
};

// same approach just using DFS - instead of going to neighbors, it would explore first current child completely deep down - complexities are same
class Solution2 {
private:
    unordered_map<string, vector<pair<string, double>>> adj; // map of 'a' -> ['b', a/b] child and its weight 
    unordered_set<string> visited;

    double dfs(const string& source, const string& target) {
        if (!adj.count(source) || !adj.count(target)) {
            return -1.0;
        }

        if (source == target) {
            return 1.0;
        }

        visited.insert(source);

        for (const auto& [neighbor, weight] : adj[source]) {
            if (!visited.count(neighbor)) {
                double result = dfs(neighbor, target);
                if (result != -1.0) {
                    return weight * result;
                }
            }
        }

        return -1.0;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // building the graph
        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];

            adj[a].emplace_back(b, values[i]);
            adj[b].emplace_back(a, 1.0 / values[i]);
        } 

        vector<double> result;
        for (const auto& query : queries) {
            string source = query[0];
            string target = query[1];
            visited.clear();
            result.push_back(dfs(source, target));
        }

        return result;
    }
};

// dsu - connecting the components where division of those two nodes exists and also if they don't have same parent then return -1 but if it does existing store the weights in such a way that there ratio distance from parent remains the same so it affects both equally as they have same parent
// we have to do this since we have to track the ratio weights as we're going through the path
// Eg: weight[x] -> represents x/root(x)
// a/b = 2, b/c = 3, query(a/c)
// now unite (a,b, 2) make b parent of a so weight[a] = 2 (means its weight is 2 times the parent) as a/b = 2, Now tree a->b is weight of 2.
// unite(b, c, 3) make c the parent so weight[b] = 3
// tree (a -> b -> c) = now path clearance happens since parent of a is b while parent of b is c 
// so weight[b] stays same while parent[a] becomes c but also weight[a] = weight[a] * weight[b] = 2 * 3 = 6
// Hence (a -> c) = weight[a] = 6 in O(1)! - using getRation(a, c) => weight[a] / weight[c] = 6
// O((m + n)logn), O(m + n)
class DSU {
    unordered_map<string, string> parent;
    unordered_map<string, double> weight;
public:
    void add(const string& x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            weight[x] = 1.0;
        }
    }

    string find(const string& x) {
        if (x != parent[x]) {
            string originalParent = parent[x];
            parent[x] = find(parent[x]);
            weight[x] *= weight[originalParent];
        }

        return parent[x];
    }

    void unite(const string& x, const string& y, double value) {
        add(x); add(y);
        string rootX = find(x), rootY = find(y);

        if (rootX != rootY) {
            parent[rootX] = rootY;
            weight[rootX] = value * weight[y] / weight[x];
        }
    }

    double getRatio(const string& x, const string& y) {
        if (parent.find(x) == parent.end() || parent.find(y) == parent.end() || find(x) != find(y)) {
            return -1.0;
        }
        
        return weight[x] / weight[y];
    }
};

class Solution3 {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        DSU dsu;

        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];

            dsu.unite(a, b, values[i]);
        }

        vector<double> result;
        for (const auto& query : queries) {
            string a = query[0];
            string b = query[1];

            result.push_back(dsu.getRatio(a, b));
        }

        return result;
    }
};

// using floyd warshall - it computes shortest paths between all pairs of nodes. So we're using if (a/b) is known and (b/c) is known then a/c = a/b * b/c Hence precalculating all such transitive ratios. And after preprocessing is done each query becomes easy
// O(m + n^3), O(n^2 + m) where n number of unique strings, m -> number of queries
class Solution4 {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, unordered_map<string, double>> graph;

        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];

            double value = values[i];

            graph[a][b] = value;
            graph[b][a] = 1.0 / value;
        }

        for (const auto& pair : graph) {
            const string& k = pair.first;
            for (const auto& pair1 : graph[k]) {
                const string& i = pair1.first;
                for (const auto& pair2 : graph[k]) {
                    const string& j = pair2.first;
                    if (!graph[i].count(j)) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                }
            }
        }

        vector<double> result;
        for (const auto& query : queries) {
            const string& a = query[0];
            const string& b = query[1];

            if (!graph.count(a) || !graph[a].count(b)) {
                result.push_back(-1.0);
            } else {
                result.push_back(graph[a][b]);
            }
        }

        return result;
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
