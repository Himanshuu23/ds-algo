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
        int n, ans(1); cin >> n;
        vector<int> v(n), dp(n, 1);

        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i+1; j < n; j++) {
                if (v[i] < v[j]) {
                    dp[i] = max(dp[i], 1 + dp[j]);
                    ans = max(dp[i], ans);
                }
            }
        }

        cout << ans << endl;
    }

    return 0;
}
