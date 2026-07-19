/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Spanning Tree -> contains V vertices but V-1 edges, its a tree so no cycle must be present and from one node we can go to any other node as well
// Total Spanning Tree Possible for a graph = [E C (V-1)] - number of cycles, C -> combinations
// using Kruskal's Algo - sort edges by weight, pick smallest edge that doesn't form a cyle - Union-Find approach - O(ElogE)
// if we apply Kruskal on non-connected graphs - then it returns spanning tree for each not connected component

class DSU {
	public:
		vector<int> parent, rank_;
		DSU (int n) {
			parent.resize(n);
			for (int i = 0; i < n; i++) parent[i] = i;
			rank_.assign(n, 0);
		}

		int find(int x) {
			if (parent[x] != x) {
				parent[x] = find(parent[x]);
			}
			return parent[x];
		}

		void unite(int x, int y) {
			int rootX = find(x), rootY = find(y);
			if (rootX == rootY) return;
			if (rank_[rootX] < rank_[rootY]) swap(rootX, rootY);
			parent[rootY] = rootX;
			if (rank_[rootX] == rank_[rootY]) rank_[rootX]++;
		}

		bool hasCycle(int x, int y) {
			int rootX = find(x), rootY = find(y);
			if (rootX == rootY) return true;
			unite(rootX, rootY);
			return false;
		}
};

int kruskal(int n, vector<tuple<int, int, int>> adj) {
	int cost = 0, count = 0;
	sort(adj.begin(), adj.end());
	DSU dsu(n);
	for (auto& [w, u, v] : adj) {
		if (!dsu.hasCycle(u, v)) {
			cost += w;
			count++;
			if (count == n - 1) break;
		}
	}

	return (count == n - 1) ? cost : -1;
}

// using Prim's - start from any node, always pick the smallest edge that connects to unvisited node - min heap - O(ElogV)

int prim(int n, vector<vector<pair<int, int>>>& adj) {
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});
    int cost = 0;

    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        cost += w;
        for (auto& [v, wt] : adj[u]) {
            if (!visited[v]) pq.push({wt, v});
        }
    }

    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<tuple<int, int, int>> edges;
        vector<vector<pair<int, int>>> adj(n);
        
        for (int i = 0; i < m; i++) {
            int u, v, w; cin >> u >> v >> w;
            edges.push_back({w, u, v});
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        cout << "using kruskal: " << kruskal(n, edges) << endl;
        cout << "using prim: " << prim(n, adj) << endl;
    }

    return 0;
}
