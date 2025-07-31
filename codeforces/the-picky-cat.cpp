/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) cin >> a[i];

        vector<pair<int, int>> pairs;
        for(int i = 0; i < n; ++i) pairs.emplace_back(abs(a[i]), i);

        sort(pairs.begin(), pairs.end());

        vector<int> ans(n, 0);
        for(int i = 0; i <= n / 2; ++i) ans[pairs[i].second] = 1;

        if(ans[0]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
