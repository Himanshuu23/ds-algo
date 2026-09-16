#include <bits/stdc++.h>
using namespace std;

// this problem is to learn: rerooting dp on trees/graphs - earlier used in minimum height trees problem
// brute force: bfs/dfs from each node - O(V * (V + E))
class Solution {
private:
    vector<vector<int>> adj;
    int distance;

    void dfs(int node, int parent, int d) {
        distance += d;
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            dfs(neighbor, node, d + 1);
        }
    }

public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            distance = 0;
            dfs(i, -1, 0);
            result[i] = distance;
        }

        return result;
    }
};

// using rerooting now
/*The general rerooting principle: Pick an arbitrary root (say 0). Do ONE DFS to compute the answer assuming node 0 is root. That gives you ans[0], correctly. For every other node, you don't recompute from scratch — instead you ask: "If I move the root from parent u to its child v, what exactly changes?" Only things relative to the edge u-v change; everything else about the tree's shape stays identical. So ans[v] = ans[u] + (some small adjustment).

In MHT, the "answer" per node was height (a max), and the adjustment when moving from parent to child was: "drop the path through this child, keep the other best path, add 1." That's why you needed top-2 heights — to have a fallback when you exclude the child you're moving into.

In this problem, the "answer" per node is sum of distances (a sum, not a max), so the adjustment is different in nature. When you move root from u to child v:

Every node inside v's subtree (there are count[v] of them) gets 1 step closer to the new root.
Every node outside v's subtree (there are n - count[v] of them) gets 1 step farther.

So: ans[v] = ans[u] - count[v] + (n - count[v])
O(V + E), O(V)
*/
class Solution2 {
private:
    vector<vector<int>> adj;
    vector<int> result, count;

    // calculating count and answer[0]
    void dfs1(int node, int parent, int distance, int& d) {
        d += distance;
        count[node] = 1; // including itself in the subtree count of the tree, for leaf count[node] = 1
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            dfs1(neighbor, node, distance + 1, d);
            count[node] += count[neighbor];
        }
    }

    // calculating for the rest of the nodes
    void dfs2(int node, int parent) {
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            if (result[neighbor] == -1) {
                result[neighbor] = result[node] - count[neighbor] + (adj.size() - count[neighbor]);
                dfs2(neighbor, node);
            }
        }
    } 
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        result.resize(n, -1);
        count.resize(n, 0);

        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        int d = 0;
        dfs1(0, -1, 0, d);
        result[0] = d;
        dfs2(0, -1);

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
