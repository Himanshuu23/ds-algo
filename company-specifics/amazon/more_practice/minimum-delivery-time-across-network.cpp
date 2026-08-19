#include <bits/stdc++.h>
using namespace std;

/*
*Amazon's delivery network has n hubs (0 to n-1) connected by m directed roads. Road i is given as [u, v, w] — travels from u to v taking w minutes (w ≥ 0).
A truck starts at hub k. Return the minimum time for a signal to reach all hubs from k. If any hub is unreachable, return -1.
Constraints
1 ≤ n ≤ 2×10^5, 1 ≤ m ≤ 2×10^5
0 ≤ w ≤ 10^4
Example
n=4, edges=[[2,1,1],[2,3,1],[3,4,1]], k=2  (1-indexed hubs here)
Output: 2
*/

// using dijkstra
// O((V + E)logV), O(V + E)
int minimumdeliverytime(int n, int k, vector<vector<int>>& edges) {
    k--;
    vector<vector<pair<int, int>>> adj(n);
    for (auto& edge : edges) {
        // edges are given 1-indexed though
        int u = edge[0] - 1;
        int v = edge[1] - 1;
        int w = edge[2];
        adj[u].push_back({ v, w });
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> distance(n, INT_MAX);
    distance[k] = 0;
    pq.push({ 0, k });

    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();

        if (dist > distance[u]) continue;

        for (auto& [v, w] : adj[u]) {
            if (dist + w < distance[v]) {
                distance[v] = dist + w;
                pq.push({ distance[v], v });
            }
        }
    }

    int answer = 0;
    for (int d : distance) {
        if (d == INT_MAX) {
            return -1;
        }
        answer = max(answer, d);
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
