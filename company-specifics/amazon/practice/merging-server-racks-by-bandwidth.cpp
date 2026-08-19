#include <bits/stdc++.h>
using namespace std;

/*
Amazon's data center has n servers labeled 0 to n-1. Initially, each server is its own isolated cluster. You're given a sequence of q operations, each one of two types:
["union", u, v] — merge the clusters containing servers u and v (if not already in the same cluster).
["query", u, v] — report whether u and v currently belong to the same cluster ("YES" / "NO").
Process all q operations in order and return the list of answers to all "query" operations, in order.
Additionally, at the very end, return the total number of distinct clusters remaining.
Output format: pair<vector<string>, int> — (query answers, final cluster count)
Constraints
1 ≤ n ≤ 2×10^5
1 ≤ q ≤ 2×10^5
0 ≤ u, v < n
Example
n = 5
ops = [["union",0,1], ["query",0,1], ["union",2,3], ["query",0,2], ["union",1,2], ["query",0,3]]
Output: (["YES","NO","YES"], 2)
(Clusters end as {0,1,2,3} and {4} → 2 clusters.)
*/

class DSU {
    private:
        vector<int> parent, _rank;
        int components;
    public:
        DSU (int n) {
            parent.resize(n);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
            _rank.assign(n, 0);
            components = n;
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

            if (_rank[rootX] < _rank[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;

            if (_rank[rootX] == _rank[rootY]) _rank[rootX]++;
            components--;
        }

        int totalComponents() {
            return components;
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, q; cin >> n >> q;

        DSU dsu(n);
        while (q--) {
            string operation;
            int u, v;
            cin >> operation;
            cin >> u >> v;

            if (operation == "union") {
                dsu.unite(u, v);
            } else {
                cout << (dsu.find(u) == dsu.find(v) ? "Yes" : "No") << '\n';
            }
        }
    
        cout << dsu.totalComponents() << '\n';
    }

    return 0;
}
