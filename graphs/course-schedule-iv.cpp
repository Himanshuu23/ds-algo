#include <bits/stdc++.h>
using namespace std;

// using dfs - just checking if there exists a path from [u -> v] for each 'q' queries
// O((V + E) * q), O(V + E)
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    bool dfs(int u, int v) {
        if (u == v) return true;
        if (visited[u]) return false;

        visited[u] = true;
        for (int neighbor : adj[u]) {
            if (dfs(neighbor, v)) return true;
        }
        
        return false;
    }
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        adj.resize(numCourses);
        visited.resize(numCourses);

        for (auto p : prerequisites) {
            adj[p[0]].push_back(p[1]);
        }

        vector<bool> answer;
        for (auto q : queries) {
            answer.push_back(dfs(q[0], q[1])); 
            visited.assign(numCourses, false); // resetting back the visited array
        }

        return answer;
    }
};

// using bfs - same complexity - same approach
class Solution2 {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    bool bfs(int u, int v) {
        queue<int> q;
        q.push(u);
        visited[u] = true;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            if (node == v) return true;

            for (int neighbor : adj[node]) {
                if (neighbor == v) return true;
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        return false;
    }
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        adj.resize(numCourses);
        visited.assign(numCourses, false);

        for (auto p : prerequisites) {
            adj[p[0]].push_back(p[1]);
        }

        vector<bool> result;

        for (auto q : queries) {
            result.push_back(bfs(q[0], q[1])); 
            visited.assign(numCourses, false);
        } 

        return result;
    }
};

// optimization: pre computing answers to each query in single dfs hence answering each query in O(1)
// O(V * (V + E) + m), O(V^2 + E + m) where m are number of queries
class Solution3 {
private:
    vector<vector<int>> adj;
    vector<vector<bool>> reach; // reach[u][v] = true when u can reach v
    vector<int> state;

    void dfs(int u) {
        if (state[u] == 1) return;
        state[u] = 1;

        for (int neighbor : adj[u]) {
            dfs(neighbor);
            // u can reach every node its neighbor can
            for (int k = 0; k < reach[neighbor].size(); k++) {
                if (reach[neighbor][k]) reach[u][k] = true;
            }
            reach[u][neighbor] = true;
        }
    }
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        adj.resize(numCourses);
        reach.assign(numCourses, vector<bool> (numCourses, false));
        state.assign(numCourses, 0);

        for (auto p : prerequisites) {
            adj[p[0]].push_back(p[1]);
        }

        for (int i = 0; i < numCourses; i++) {
            dfs(i);
        }

        vector<bool> answer;
        for (auto q : queries) {
            answer.push_back(reach[q[0]][q[1]]);
        }

        return answer;
    }
};

// optimization: memoization in the same approach - so we have calls pre computed and can re used those paths and don't make unnecessary calls - 
// O(V * (V + E) + m), O(V^2 + E + m) where m are number of queries
class Solution4 {
private:
    vector<vector<int>> adj;
    vector<vector<int>> dp; // 0 -> unvisited, 1 -> reachable, -1 -> unreachable
    
    bool dfs(int u, int v) {
        if (u == v) return true;
        if (dp[u][v] != 0) return dp[u][v] == 1;

        for (int neighbor : adj[u]) {
            // if neighbor can reach v, then u can reach v through its neighbor
            if (dfs(neighbor, v)) {
                dp[u][v] = 1;
                return true;
            }
        }

        dp[u][v] = -1; // unreachable
        return false;
    }
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        adj.resize(numCourses);
        dp.assign(numCourses, vector<int> (numCourses, 0));

        for (auto p : prerequisites) {
            adj[p[0]].push_back(p[1]);
        }

        vector<bool> answer;
        for (auto q : queries) {
            answer.push_back(dfs(q[0], q[1]));
        }

        return answer;
    }
};

// using Kahn's algorithm - precalculating answer to each node's prerequisite as well. So since in topological sort the nodes are processed in way that first prerequisites than the course itself. So first prerequisite's prerequisite also called complete transitive closure of the node is calculated.
// O(V * (V + E) + m), O(V^2 + E + m)
class Solution5 {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        vector<unordered_set<int>> isPrereq(numCourses); // set of all prerequisites of each node

        for (auto& p : prerequisites) {
            adj[p[0]].push_back(p[1]);
            inDegree[p[1]]++;
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                isPrereq[v].insert(u); // 'u' is prereq of 'v'
                isPrereq[v].insert(isPrereq[u].begin(), isPrereq[u].end()); // all prereq of 'u' also become prereq of 'v'
                if (--inDegree[v] == 0) q.push(v); 
            }
        }

        vector<bool> answer;
        for (auto& query : queries) {
            answer.push_back(isPrereq[query[1]].count(query[0]));
        }

        return answer;
    }
};

// using floyd warshall algorithm
// O(V^3 + E + m), O(V^2 + E + m)
class Solution6 {
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool>> adj(numCourses, vector<bool>(numCourses, false));
        vector<bool> res;

        for (auto& pre : prerequisites) {
            adj[pre[0]][pre[1]] = true;
        }

        for (int k = 0; k < numCourses; k++) {
            for (int i = 0; i < numCourses; i++) {
                for (int j = 0; j < numCourses; j++) {
                    adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
                }
            }
        }

        for (auto& q : queries) {
            res.push_back(adj[q[0]][q[1]]);
        }

        return res;
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
