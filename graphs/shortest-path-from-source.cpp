/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Dijkstra - directed + undirected, no negative cycles though -> O(V+E)logV
// Bellman Ford - can be used for negative weights as well and detects negative cycles -> O(V.E) -> and in the complete graph say we have n vertices then O(n2) generally but complete graph means every node connected to each other so total edges n(n-1)/2 hence it becomes O(n3). Also bellman ford works for negative weights but if there is a cycle with negative weight then it would keep running even after (n-1) times so never terminates, n -> number of edges.
// Kahn - topological sort + dp - works for DAGs, also handles negative weights! just not cycles -> O(V+E)

vector<int> dijkstra(int n, vector<vector<pair<int, int>>>& adj, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<int> bellmanFord(int n, vector<tuple<int, int, int>>& edges, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i < n; i++) {
        for (auto& [u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) dist[v] = dist[u] + w;
        }
    }

    // for detecting negative cycles
    for (auto& [u, v, w] : edges) 
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) throw runtime_error("Negative weight cycle detected!");
    return dist;
}

vector<int> kahn(int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> inDegree(V, 0);
    for (int i = 0; i < V; i++) {
        for (auto& [v,w]: adj[i]) inDegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    vector<int> topological;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topological.push_back(u);
        for (auto [v, w] : adj[u]) {
            if (--inDegree[v] == 0) q.push(v);
        }
    }

    if (topological.size() != V) return {};

    return topological;
}

void shortestPathKahn(vector<vector<pair<int, int>>>& adj, int source) {
    int V = adj.size();
    vector<int> topological = kahn(V, adj);

    vector<int> distance(V, INT_MIN);
    distance[source] = 0;
    for (int u : topological) {
        if (distance[u] != INT_MIN) {
            for (auto [v, w] : adj[u]) {
                if (distance[v] > distance[u] + w) distance[v] = distance[u] + w;
            }
        }
    }

    for (int i = 0; i < V; i++) {
        cout << "Shortest Distance from source to " << i << " -> " << (distance[i] == INT_MIN ? -1 : distance[i]) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<vector<pair<int, int>>> adj(n);
        vector<tuple<int, int, int>> edges;

        for (int i = 0; i < m; i++) {
            int u, v, w; cin >> u >> v >> w;
            adj[u].push_back({v, w});
            edges.emplace_back(u, v, w);
        }

        int src; cin >> src;

        auto d1 = dijkstra(n, adj, src);
        auto d2 = bellmanFord(n, edges, src);

        cout << "Dijkstra: ";
        for (int d : d1) cout << d << " "; cout << endl;
    
        cout << "Bellman-Ford: ";
        for (int d : d2) cout << d << " "; cout << endl;
    }

    return 0;
}
