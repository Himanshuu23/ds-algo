#include <bits/stdc++.h>
using namespace std;

// Brute force: using dfs - build graph - dfs from each node -> find height - mark the minimum ones - if there are total 'V' nodes -> O(V * (V + E)), O(V)
class Solution {
private:
    vector<vector<int>> adj;

    int height(int node, int parent) {
        int h = 0;
        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            h = max(h, height(neighbor, node));
        }

        return 1 + h;
    }
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        adj.resize(n);

        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> heights;
        for (int i = 0; i < n; i++) {
            heights.push_back(height(i, -1));
        }

        int required = *min_element(heights.begin(), heights.end());

        vector<int> result;
        for (int i = 0; i < n; i++) {
            if (heights[i] == required) {
                result.push_back(i);
            }
        }

        return result;
    }
};

// dp on trees (rerooting) - reusing precomputed answers: height of tree rooted at any node x = longest downward path from that node. Now we find two paths not [best, second_best]. second_best coz longest path might go through the same current neighbor we're exploring.
// two pass dfs. first dfs: post order - taking some arbitrary node as root. dp[node][0] = best, dp[node][1] = second_best. - find the best, second best height for each node with some single node as 0
// second dfs: preorder, - if we stood at this parent then how tall rest of tree would be updating earlier calculated child heights accordingly
// O(V + E), O(V)
class Solution2 {
    private:
        vector<vector<int>> adj;
        vector<vector<int>> dp;
    
        void dfs1(int node, int parent) {
            for (int neighbor : adj[node]) {
                if (neighbor == parent) continue;
                dfs1(neighbor, node);
                int current_height = 1 + dp[neighbor][0];
                if (current_height > dp[node][0]) {
                    dp[node][1] = dp[node][0];
                    dp[node][0] = current_height;
                } else if (current_height > dp[node][1]) {
                    dp[node][1] = current_height;
                }
            }
        }

        // dfs2 - pre order - pushing the upward height down from parent to child
        void dfs2(int node, int parent, int top_height) {
            // top_height = best height achievable going up through parent NOT through this node 
            if (top_height > dp[node][0]) {
                dp[node][1] = dp[node][0];
                dp[node][0] = top_height;
            } else if (top_height > dp[node][1]) {
                dp[node][1] = top_height;
            }

            for (int neighbor : adj[node]) {
                if (neighbor == parent) continue;
                // if node's best height came through this child, pass the second best instead (to avoid using same path again)
                int toChild = 1 + ((dp[node][0] == 1 + dp[neighbor][0]) ? dp[node][1] : dp[node][0]);
                dfs2(neighbor, node, toChild);
            }
        }

    public:
        vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
            if (n == 1) return {0};

            adj.resize(n);
            dp.assign(n, vector<int> (2, 0));
            for (const auto& edge : edges) {
                adj[edge[0]].push_back(edge[1]);
                adj[edge[1]].push_back(edge[0]);
            }

            dfs1(0, -1);
            dfs2(0, -1, 0);

            int minHeight = n;
            for (int i = 0; i < n; i++) {
                minHeight = min(minHeight, dp[i][0]);
            }

            vector<int> result;
            for (int i = 0; i < n; i++) {
                if (dp[i][0] == minHeight) result.push_back(i);
            }

            return result;
        }
};

// for trees: if we find farthest point from any node then that is one end of the diameter always. 
// Approach: min height would be present at the centroid of the tree i.e. middle of the diameter path of the tree since we're minimizing/balancing the distance between farthest height of the tree.
// First from random node find farthest node say A (one end of the diameter) then from A also find the farthest node using bfs/dfs call B. Now, A-B is the diameter then middle of that diameter from A-B inorder there centre is the required root. If odd number of nodes then single root exists if even then two in the centre.
// O(V + E), O(V)
class Solution3 {
private:
    vector<vector<int>> adj;

    // to find the farthest node from some starting node, and also building the parent array to construct back the path
    int dfs(int node, int parent, int distance, vector<int>& parents, pair<int, int>& farthest) {
        parents[node] = parent;
        if (distance > farthest.second) {
            farthest = { node, distance };
        }

        for (int neighbor : adj[node]) {
            if (neighbor == parent) continue;
            dfs(neighbor, node, distance + 1, parents, farthest);
        }

        return farthest.first;
    }
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};
        if (n == 2) return {0, 1}; // both nodes are centroids of a single edge
        
        adj.resize(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // finding 'A'
        vector<int> parent1(n, -1);
        pair<int, int> farthest1 = {0, 0};
        int A = dfs(0, -1, 0, parent1, farthest1);

        // finding 'B' - farthest point from 'A'
        vector<int> parent2(n, -1);
        pair<int, int> farthest2 = {0, 0};
        int B = dfs(A, -1, 0, parent2, farthest2);

        // reconstructing path back from B->A
        vector<int> path; 
        int current = B;
        while (current != -1) {
            path.push_back(current);
            current = parent2[current];
        }

        // path is [B...A] - finding centre still remains the same
        int length = path.size();
        vector<int> result;
        if (length & 1) {
            result.push_back(path[length / 2]);
        } else {
            result.push_back(path[length/2 - 1]);
            result.push_back(path[length/2]);
        }

        return result;
    }
};

// using topological sort (bfs): like peeling a onion - removing layer by layer - we remove nodes and in the end centroid would be remaining. Since the tree can have atmost 2 centroids so we stop when 2 or less remain. So if odd number of nodes single centroid else for even we would have two.
// push all leaf nodes in the queue, remove them one by one and also decrease their neighbour's degree and if after reducing the neighbor degree they become leaf push them also in the queue
// O(V + E), O(V)
class Solution4 {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};

        vector<vector<int>> adj(n);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<int> edge_count(n);
        queue<int> leaves;

        for (int i = 0; i < n; i++) {
            edge_count[i] = adj[i].size();
            if (adj[i].size() == 1) {
                leaves.push(i);
            }
        }

        while (!leaves.empty()) {
            if (n <= 2) {
                vector<int> result;
                while (!leaves.empty()) {
                    result.push_back(leaves.front());
                    leaves.pop();
                }
                return result;
            }

            int size = leaves.size();
            for (int i = 0; i < size; i++) {
                int node = leaves.front();
                leaves.pop();
                --n;
                for (int& neighbor : adj[node]) {
                    --edge_count[neighbor];
                    if (edge_count[neighbor] == 1) {
                        leaves.push(neighbor);
                    }
                }
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
