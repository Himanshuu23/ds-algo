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
        int n, m, ans(0); cin >> n >> m;
        string a, b; cin >> a >> b;
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for (int i = n-1; i>=0; i--) {
            for (int j = m-1; j>=0; j--) {
                if (a[i] == b[j]) dp[i][j] = 1 + dp[i+1][j+1];
                else dp[i][j] = 0;
                ans = max(ans, dp[i][j]);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
