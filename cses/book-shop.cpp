#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        int n, x;
        cin >> n >> x;
        vector<int> price(n), pages(n);
        for (int i = 0; i < n; i++) {
            cin >> price[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> pages[i];
        }
    
        vector<vector<int>> dp(n + 1, vector<int> (x + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= x; j++) {
                int exclude = dp[i-1][j];
                int include = INT_MIN;
                if (j - price[i-1] >= 0) include = pages[i-1] + dp[i-1][j-price[i-1]];
                dp[i][j] = max(include, exclude);
            }
        }

        cout << dp[n][x] << '\n';
    }

    return 0;
}
