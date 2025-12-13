#include <bits/stdc++.h>
using namespace std;

int minDrops(int k, int n, vector<vector<int>> &dp) {
    if (k == 1) return n;
    if (n <= 0) return 0;
    if (n == 1) return 1;
    if (dp[k][n] != INT_MAX) return dp[k][n];

    for (int z = 1; z <= n; z++)
        dp[k][n] = min(dp[k][n], 1 + max(minDrops(k-1, z-1, dp), minDrops(k, n-z, dp)));
    return dp[k][n];
}

int main() {
    int k, n; cin >> k >> n;
    vector<vector<int>> dp(k+1, vector<int> (n+1, INT_MAX));

    cout << minDrops(k, n, dp) << endl;

    return 0;
}
