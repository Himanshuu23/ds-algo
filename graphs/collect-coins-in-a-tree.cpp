#include <bits/stdc++.h>
using namespace std;

// this problem is to practice - peeling off topological sort used in minimum height trees problem

// brute force: O(V^2) - First remove all the leaf nodes that have no coins since they're unecessary for sure (unbounded). Then in the second pass we're left minimized subtree already where all leaf nodes have coins means we can remove from each leaf node -> multi bfs -> remove two more nodes from each since they're reachable from there and hence in the end we have the required subtree that is minimized.
class Solution {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();
        vector<set<int>> adj(n);

        for (auto& edge : edges) {
            adj[edge[0]].insert(edge[1]);
            adj[edge[1]].insert(edge[0]);
        }
    
        // removing the leaf nodes with no coins (unbounded)
        bool removedSomething = true;
        while (removedSomething) {
            removedSomething = false;
            vector<int> currentLeaves;
            for (int i = 0; i < n; i++) {
                if (adj[i].size() == 1 && !coins[i]) {
                    currentLeaves.push_back(i);
                }
            }

            if (!currentLeaves.empty()) {
                int leaf = currentLeaves[0];
                int neighbor = *adj[leaf].begin();
                adj[leaf].erase(neighbor);
                adj[neighbor].erase(leaf);
                removedSomething = true;
            }
        }

        // remove ANY leaf node -> 2
        for (int round = 0; round < 2; round++) {
            vector<int> currentLeaves;
            for (int i = 0; i < n; i++) {
                if (adj[i].size() == 1) {
                    currentLeaves.push_back(i);
                }
            }

            for (int leaf : currentLeaves) {
                if (adj[leaf].empty()) continue;
                int neighbor = *adj[leaf].begin();
                adj[leaf].erase(neighbor);
                adj[neighbor].erase(leaf);
            }
        }

        int remainingEdges = 0;
        for (int i = 0; i < n; i++) {
            remainingEdges += adj[i].size();
        }

        return remainingEdges;
    }
};

// O(V) - using "peel off" toplogical sort - just same approach. Optimization: in the first phase we're recomputing for the new leaf nodes but here we can just push the new leaf nodes into the queue and hence continue while queue isn't empty.
class Solution2 {
public:
    int collectTheCoins(vector<int>& coins, vector<vector<int>>& edges) {
        int n = coins.size();

        vector<set<int>> adj(n);
        vector<int> indegree(n);

        for (auto& edge : edges) {
            adj[edge[0]].insert(edge[1]);
            adj[edge[1]].insert(edge[0]);
            indegree[edge[0]]++;
            indegree[edge[1]]++;
        }

        int remainingEdges = n - 1; // total edges initially

        // trimming the non coin leaf nodes
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1 && coins[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int leaf = q.front();
            q.pop();

            indegree[leaf]--;
            remainingEdges--;

            for (int neighbor : adj[leaf]) {
                if (indegree[neighbor] == 0) continue; // already removed
                if (--indegree[neighbor] == 1 && coins[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        // trimming two more nodes from each coin leaf nodes
        for (int round = 0; round < 2; round++) {
            vector<int> leaves;
            for (int i = 0; i < n; i++) {
                if (indegree[i] == 1) {
                    leaves.push_back(i);
                }
            }

            for (int leaf : leaves) {
                indegree[leaf]--;
                remainingEdges--;
                for (int neighbor : adj[leaf]) {
                    if (indegree[neighbor] > 0) {
                        indegree[neighbor]--;
                    }
                }
            }
        }

        remainingEdges = max(remainingEdges, 0);
        return remainingEdges * 2;
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
