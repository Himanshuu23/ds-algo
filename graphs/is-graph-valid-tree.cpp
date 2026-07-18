/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// approach - union-find --> if any edge, connect two nodes in the same set -> cycle. After processing all edges, check if there's exactly one connected component
/*
conditions for graph to be tree :- 
(1) every node is connected and can be reached from some other node
(2) No cycles 
(3) n nodes -> exactly n-1 edges
tree = connected acyclic graph
*/

class DSU {
    public: 
        vector<int> parent, rank_;
        DSU(int n) {
            parent.resize(n);
            rank_.assign(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find (int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }

        void unite(int x, int y) {
            int parentX = find(x), parentY = find(y);
            if (parentX == parentY) return;

            if (rank_[parentX] < rank_[parentY]) swap(parentX, parentY);
            parent[parentY] = parentX;
            if (rank_[parentX] == rank_[parentY]) rank_[parentX]++;
        }

        bool hasCycle(int u, int v) {
            int parentU = find(u), parentV = find(v);
            if (parentU == parentV) return true;
            unite(parentU, parentV);
            return false;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int V, E; cin >> V >> E;
        DSU dsu(V);
        bool isTree = true;
        for (int i = 0; i < E; i++) {
            int u, v; cin >> u >> v;
            if (dsu.hasCycle(u, v))
                isTree = false;
        } 

        if (E != V - 1) isTree = false;

        cout << isTree << '\n';
    }

    return 0;
}
