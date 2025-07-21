/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int, int> solve(int n, const vector<int>& v, int target) {
    unordered_map<int, int> mp;
    int prefix(0);

    for (int i = 0; i < n; i++) {
        prefix = target - v[i];
        if (mp.count(prefix)) return {mp[prefix], i};
        mp[v[i]] = i;
    }

    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, target; cin >> n >> target;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        pair<int, int> p = solve(n, v, target);
        cout << p.first << " " << p.second << '\n';
    }

    return 0;
}
