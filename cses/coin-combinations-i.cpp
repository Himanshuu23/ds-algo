#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        const long long MOD = 1e9 + 7;
        int n;
        long long x;
        cin >> n >> x;
        vector<long long> coins(n);
        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }
        vector<long long> dp(x + 1);
        dp[0] = 1;

        for (long long i = 1; i <= x; i++) {
            for (long long j : coins) {
                if (i - j >= 0) {
                    dp[i] = (dp[i] + dp[i - j]) % MOD;
                }
            }
        }

        cout << (dp[x] % MOD) << '\n';
    }

    return 0;
}
