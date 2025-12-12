#include <bits/stdc++.h>
using namespace std;

int findMaximumCoins(int l, int r, vector<int> &v, vector<vector<int>> &dp) {
    if (l > r) return 0;
    if (l == r) return v[l-1]*v[l]*v[r+1];
    if (dp[l][r] != INT_MIN) return dp[l][r];
    
    for (int k = l; k <= r; k++) {
        int coins = findMaximumCoins(l, k-1, v, dp) + findMaximumCoins(k+1, r, v, dp) + v[l-1]*v[k]*v[r+1];
        dp[l][r] = max(dp[l][r], coins);
    }

    return dp[l][r];
}

int main() {
    int n; cin >> n;
    vector<int> v(n+2);
    vector<vector<int>> dp(n+2, vector<int> (n+2, INT_MIN));

    for (int i = 1; i < n+1; i++) cin >> v[i];
    v[0] = v[n+1] = 1;

    cout << findMaximumCoins(1, n, v, dp) << endl;

    return 0;
}
