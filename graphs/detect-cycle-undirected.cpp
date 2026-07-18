/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class DSU {
    public:
        vector<int> parent, rank_;
        DSU(int n) {
            parent.resize(n);
            rank_.assign(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
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

        bool detectCycle(int u, int v) {
            int pu = find(u), pv = find(v);
            if (pu == pv) return true;
            unite(pu, pv);
            return false;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;

        DSU dsu(V);
        bool hasCycle = false;
        for (int i = 0; i < E; ++i) {
            int u, v; cin >> u >> v;

            if (dsu.detectCycle(u, v)) {
                hasCycle = true;
            }
        }

        if (hasCycle)
            cout << "Cycle detected\n";
        else
            cout << "No cycle\n";
    }

    return 0;
}
