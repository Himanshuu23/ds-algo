/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> floydWarshall(int n, vector<tuple<int, int, int>>& edges) { // O(V3)
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& [u, v, w] : edges) dist[u][v] = min(dist[u][v], w);

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    
    return dist;
}

vector<vector<int>> bellmanford(int n, vector<tuple<int, int, int>>& adj) { // O(V2E)
	vector<vector<int>> answer(n, vector<int> (n, INT_MAX));

	for (int source = 0; source < n; source++) {
		answer[source][source] = 0;
		for (int i = 1; i < n; i++) {
			for (auto& [u, v, w] : adj) {
				if (answer[source][u] != INT_MAX && answer[source][v] > answer[source][u] + w) answer[source][v] = answer[source][u] + w;
			}
		}
	}

	return answer;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<tuple<int, int, int>> edges;

        for (int i = 0; i < m; i++) {
            int u, v, w; cin >> u >> v >> w;
            edges.push_back({u, v, w});
        }
        
        auto d = floydWarshall(n, edges);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << (d[i][j] == INT_MAX ? -1 : d[i][j]) << " ";
            cout << endl;
        }
    }

    return 0;
}
