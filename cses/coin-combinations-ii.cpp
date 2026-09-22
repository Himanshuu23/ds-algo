#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        // for distinct doing coins first works coz suppose for coins = [2,3] and x = 5. We would have problem: 2 + 3 and 3 + 2 but using these coins for coin = 2 first dp[5-3] = dp[3] wouldn't be calculated. then for coin = 3 its calculated for the first time that is dp[5-3] = dp[2] = 1

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

        for (long long j : coins) {
            for (int i = 1; i <= x; i++) {
                if (i - j >= 0) {
                    dp[i] = (dp[i] + dp[i - j]) % MOD;
                }
            }
        }

        cout << (dp[x] % MOD) << '\n';
    }

    return 0;
}
