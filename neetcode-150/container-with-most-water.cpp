/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n, vector<int>& v) {
    int l(0), r(n-1), ans(0);
    while (l < r) {
        int ht = min(v[l], v[r]);
        int area = (r - l) * ht;
        ans = max(ans, area);
        (v[l] <= v[r]) ? l++ : r--;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(n, v) << endl;
    }

    return 0;
}
