#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        int n;
        long long x;
        cin >> n >> x;
        vector<long long> coins(n);
        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }
        vector<long long> dp(x + 1, INT_MAX);
        dp[0] = 0;

        for (long long i = 1; i <= x; i++) {
            for (long long coin : coins) {
                if (i - coin >= 0 && dp[i-coin] != INT_MAX) {
                    dp[i] = min(dp[i], 1 + dp[i-coin]);
                }
            }
        }

        cout << (dp[x] == INT_MAX ? -1 : dp[x]) << '\n';
    }

    return 0;
}
