/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// using dfs - cycle detection - O(V + E), O(V + E)
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    bool dfs(int course) {
        if (visited[course]) {
            return false; // cycle detected
        }
        if (adj[course].empty()) {
            return true;
        }

        visited[course] = true;
        for (int pre : adj[course]) {
            if (!dfs(pre)) {
                return false;
            }
        }

        visited[course] = false;
        adj[course] = {};
        return true;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        visited.resize(numCourses, false);
        adj.resize(numCourses);

        for (auto p : prerequisites) {
            adj[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i)) {
                return false;
            }
        }

        return true;
    }
};

// approach - using Kahan's Algorithm - (BFS + Topological Sort) - O(V + E), O(V + E)
bool canFinish(int numCourse, vector<vector<int>>& prereq) {
    vector<vector<int>> adj(numCourse);
    vector<int> inDegree(numCourse, 0);

    for (auto& p : prereq) {
        adj[p[1]].push_back(p[0]);
        inDegree[p[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourse; i++) 
        if (inDegree[i] == 0) q.push(i);

    int count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v : adj[u])
            if (--inDegree[v] == 0) q.push(v);
    }

    return count == numCourse;
}

// same dfs method but if we want the order as well
class Solution2 {
private:
    vector<vector<int>> adj;
    vector<int> state; // 0 = unvisited, 1 = currently processing, 2 = processed
    vector<int> result;

    bool dfs(int course) {
        if (state[course] == 1) return false;
        if (state[course] == 2) return true;

        state[course] = 1;
        for (int pre : adj[course]) {
            if (!dfs(pre)) {
                return false;
            }
        }

        state[course] = 2;
        result.push_back(course);
        return true;
    }
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        adj.resize(numCourses);
        state.assign(numCourses, 0);

        for (auto& p : prerequisites) {
            adj[p[1]].push_back(p[0]);
        }

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(i)) {
                return {};
            }
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> pre(m);
        for (int i = 0; i < n; i++) {
            int a, b; cin >> a >> b;
            pre[i] = {a, b};
        }

        cout << (canFinish(n, pre) ? "Yes" : "No") << endl;
    }

    return 0;
}
