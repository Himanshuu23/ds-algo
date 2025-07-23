/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n, vector<int>& h) {
    int l(0), r(n - 1), lm(0), rm(0), ans(0);

    while (l <= r) {
        if (h[l] <= h[r]) {
            if (h[r] >= lm) lm = h[l];
            else ans += lm - h[l];
            l++;
        } else {
            if (h[r] >= rm) rm = h[r];
            else ans += rm - h[r];
            r--;
        }
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
