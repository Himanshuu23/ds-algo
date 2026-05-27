#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n, W; cin >> n >> W;
        vector<int> v(n), w(n);

        for (int i = 0; i < n; i++)
            cin >> v[i];

        for (int i = 0; i < n; i++)
            cin >> w[i];

        vector<vector<int>> dp(n+1, vector<int> (W+1));
        for (int i = 0; i < n+1; i++)
            dp[i][0] = 0;

        for (int i = 0; i < W+1; i++)
            dp[0][i] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= W; j++) {
                int include = INT_MIN, exclude = INT_MIN;
                exclude = dp[i-1][j];
                if (j >= w[i-1]) include = v[i-1] + dp[i-1][j-w[i-1]];
                dp[i][j] = max(include, exclude);
            }
        }

        cout << dp[n][W] << '\n';
    }

    return 0;
}
