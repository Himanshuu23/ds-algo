/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(vector<int>& v) {
    int l(0), r(v.size() - 1);

    while (l < r) {
        int mid = (l + r) / 2;

        if (v[r] < v[mid]) l = mid + 1;
        else r = mid;
    }

    return v[l];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(v) << endl;
    }

    return 0;
}
