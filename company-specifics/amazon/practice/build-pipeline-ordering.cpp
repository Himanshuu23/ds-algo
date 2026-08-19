#include <bits/stdc++.h>
using namespace std;

/*
Amazon's internal build system compiles a set of n services, labeled 0 to n-1. Some services depend on others being built first, given as a list of pairs dependencies[i] = [a, b] meaning service a must be built before service b.
Return any valid build order of all n services such that every dependency is respected. If no valid order exists (a circular dependency exists), return an empty array.
Additionally: if there are multiple valid orders, return the lexicographically smallest one (build lower-numbered available services first when there's a choice).
Constraints
1 ≤ n ≤ 10^5
0 ≤ dependencies.length ≤ 10^5
dependencies[i].length == 2
Example
n = 6
dependencies = [[2,1],[2,5],[1,0],[5,0],[0,3],[4,3]]
Output: [2,1,4,5,0,3]
*/

// kahn algorithm for topological sort + priority queue to get minimum node for lexicographically smallest
// O((V+E)logV), O(V+E)
vector<int> buildPiplelineOrdering(int n, vector<vector<int>>& dependencies) {
    vector<int> inDegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : dependencies[u]) {
            inDegree[v]++;
        } 
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> result;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        result.push_back(u);

        for (int v : dependencies[u]) {
            if (--inDegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    if (result.size() != n) return {};

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> dependencies(n);
        for (int i = 0; i < m; i++) {
            int a, b; cin >> a >> b;
            dependencies[a].push_back(b);
        }

        vector<int> result = buildPiplelineOrdering(n, dependencies);
        for (int x : result) {
            cout << x << " ";
        }
        cout << '\n';
    }

    return 0;
}
