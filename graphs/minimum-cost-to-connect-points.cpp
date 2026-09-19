#include <bits/stdc++.h>
using namespace std;

// using kruskal - O(n^2 logn), O(n^2)
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

		bool unite(int x, int y) {
			int rootX = find(x), rootY = find(y);
			if (rootX == rootY) return false;
			if (rank_[rootX] < rank_[rootY]) swap(rootX, rootY);
			parent[rootY] = rootX;
			if (rank_[rootX] == rank_[rootY]) rank_[rootX]++;
            return true;
		}
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        DSU dsu(n);
        vector<vector<int>> edges;

        auto manhattan = [](int a, int b, int c, int d) {
            return abs(a - c) + abs(b - d);
        };

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges.push_back({manhattan(points[i][0], points[i][1], points[j][0], points[j][1]), i, j});
            }
        }

        sort(edges.begin(), edges.end());
        
        int answer = 0;
        for (auto& edge : edges) {
            int distance = edge[0], u = edge[1], v = edge[2];
            if (dsu.unite(u, v)) {
                answer += distance;
            }
        }

        return answer;
    }
};

// using prims - O(n^2 logn), O(n^2)
class Solution2 {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<vector<int>>> edges(n);

        auto manhattan = [](int a, int b, int c, int d) {
            return abs(a - c) + abs(b - d);
        };

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges[i].push_back({manhattan(points[i][0], points[i][1], points[j][0], points[j][1]), j});
                edges[j].push_back({manhattan(points[i][0], points[i][1], points[j][0], points[j][1]), i});
            }
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        set<int> visited;
        
        int answer = 0;
        pq.push({0, 0});

        while (visited.size() < n) {
            auto current = pq.top();
            pq.pop();

            int cost = current[0];
            int i = current[1];
            if (visited.count(i)) continue;

            visited.insert(i);
            answer += cost;
            for (auto& neighbor : edges[i]) {
                int neighbor_cost = neighbor[0], neighbor_index = neighbor[1];
                if (!visited.count(neighbor_index)) {
                    pq.push({neighbor_cost, neighbor_index});
                }
            }
        }

        return answer;
    }
};

// optimized prims - O(n^2), O(n) - just not building all edges but connect on the go for each node best possible node only since for each node we just have to find single node
class Solution3 {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<vector<int>>> edges(n);

        auto manhattan = [](int a, int b, int c, int d) {
            return abs(a - c) + abs(b - d);
        };

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                edges[i].push_back({manhattan(points[i][0], points[i][1], points[j][0], points[j][1]), j});
                edges[j].push_back({manhattan(points[i][0], points[i][1], points[j][0], points[j][1]), i});
            }
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        set<int> visited;
        
        int answer = 0;
        pq.push({0, 0});

        while (visited.size() < n) {
            auto current = pq.top();
            pq.pop();

            int cost = current[0];
            int i = current[1];
            if (visited.count(i)) continue;

            visited.insert(i);
            answer += cost;
            for (auto& neighbor : edges[i]) {
                int neighbor_cost = neighbor[0], neighbor_index = neighbor[1];
                if (!visited.count(neighbor_index)) {
                    pq.push({neighbor_cost, neighbor_index});
                }
            }
        }

        return answer;
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
