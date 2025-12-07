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
        int n, m; cin >> n >> m;
        string a, b; cin >> a >> b;
        vector<vector<int>> dp(n+1, vector<int> (m+1, INT_MAX));

        for (int i = 0; i < n + 1; i++) dp[i][m] = n - i;
        for (int j = 0; j < m + 1; j++) dp[n][j] = m - j;

        for (int i = n-1; i>=0;i--) {
            for (int j = m-1; j>=0;j--) {
                if (a[i] == b[j]) dp[i][j] = dp[i+1][j+1];
                else dp[i][j] = 1 + min({dp[i+1][j+1], dp[i+1][j], dp[i][j+1]});
            }
        }

        cout << dp[0][0] << endl;
    }

    return 0;
}
