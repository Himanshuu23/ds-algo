#include <bits/stdc++.h>
using namespace std;

// This is like building a directed graph where A->B edge means A must come before B in the matrix. -> topological sort
// do topological sort on both row and column conditions and make matrix using orderings of each
// if there are cycles then no valid ordering exists return {}
// using dfs: O(k^2 + n + m), space: O(k + n + m) extra space, O(k^2) for output matrix where n is size of row conditions, m is size of column conditions and k is the size of the output matrix
class Solution {
private:
    vector<bool> visited, path;
    vector<int> order;
    vector<vector<int>> adj;

    vector<int> topologicalSort(int k, vector<vector<int>> edges) {
        adj.assign(k + 1, {});
        visited.assign(k + 1, false);
        path.assign(k + 1, false);
        order.clear();

        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
        }

        for (int i = 1; i <= k; i++) {
            if (!visited[i]) {
                if (!dfs(i)) { // cycle exists
                    return {};
                }
            }
        }

        reverse(order.begin(), order.end());
        return order;
    }

    bool dfs(int source) {
        if (path[source]) return false; // if current path already contains this node
        if (visited[source]) return true; // this node is full processed already

        path[source] = true;
        visited[source] = true;
        for (int neighbor : adj[source]) {
            if (!dfs(neighbor)) {
                return false;
            }
        }

        path[source] = false; // node is full processed so remove from current path
        order.push_back(source); // node is pushed when all its children have been processed
        return true;
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<int> rowOrder = topologicalSort(k, rowConditions);
        if (rowOrder.empty()) return {};
    
        vector<int> columnOrder = topologicalSort(k, colConditions);
        if (columnOrder.empty()) return {};

        unordered_map<int, int> valToRow, valToCol; // mapping elements order from each ordering
        for (int i = 0; i < rowOrder.size(); i++) {
            valToRow[rowOrder[i]] = i;
        }

        for (int i = 0; i < columnOrder.size(); i++) {
            valToCol[columnOrder[i]] = i;
        }

        vector<vector<int>> result(k, vector<int> (k));
        for (int num = 1; num <= k; num++) {
            int r = valToRow[num];
            int c = valToCol[num];
            result[r][c] = num;
        }

        return result;
    }
};

// logic exactly same just topological sort using kahn's algorithm - much simpler than dfs
// in kahn's cycle detection is when all nodes not processed - so here order.size() != k then cycle exists
// complexities remain same
class Solution2 {
private:
    vector<int> topologicalSort(int k, vector<vector<int>>& edges) {
        vector<int> indegree(k + 1, 0);
        vector<vector<int>> adj(k + 1);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }

        queue<int> q;
        vector<int> order;
        for (int i = 1; i <= k; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            order.push_back(node);

            for (int neighbor : adj[node]) {
                if (--indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (order.size() != k) return {}; // cycle exists

        return order;
    }
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<int> rowOrder = topologicalSort(k, rowConditions);
        if (rowOrder.empty()) return {};
    
        vector<int> columnOrder = topologicalSort(k, colConditions);
        if (columnOrder.empty()) return {};

        unordered_map<int, int> valToRow, valToCol; // mapping elements order from each ordering
        for (int i = 0; i < rowOrder.size(); i++) {
            valToRow[rowOrder[i]] = i;
        }

        for (int i = 0; i < columnOrder.size(); i++) {
            valToCol[columnOrder[i]] = i;
        }

        vector<vector<int>> result(k, vector<int> (k));
        for (int num = 1; num <= k; num++) {
            int r = valToRow[num];
            int c = valToCol[num];
            result[r][c] = num;
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
