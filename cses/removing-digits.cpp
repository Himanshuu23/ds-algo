#include <bits/stdc++.h>
using namespace std;

/*
brute force
    long long x = 0, steps = 0;
    while (n) {
        x = n;
        int mx = 0;
        while (n) {
            mx = max(1LL*mx, n % 10);
            n /= 10;
        }
        n = x;
        n -= mx;
        ++steps;
    }

    cout << steps << '\n';
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        long long n; cin >> n;
        
        // bottom up
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++) {
            dp[i] = 1e9;
            int i2 = i;
            while (i2) {
                dp[i] = min(dp[i], dp[i - i2 % 10] + 1);
                i2 /= 10;
            }
        }

        cout << dp[n] << '\n';
    }

    return 0;
}
