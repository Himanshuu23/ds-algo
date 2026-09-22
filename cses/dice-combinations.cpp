#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        const long long MOD = 1e9 + 7;
        long long n; cin >> n;
        vector<long long> dp(n + 1);
        dp[0] = 1;

        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= 6; j++) {
                if (i - j >= 0) {
                    dp[i] = (dp[i] + dp[i - j]) % MOD;
                }
            }
        }

        cout << (dp[n] % MOD) << '\n';
    }

    return 0;
}
