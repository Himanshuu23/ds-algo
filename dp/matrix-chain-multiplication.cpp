#include <bits/stdc++.h>
using namespace std;

int matrixChainMultiplication(int i, int j, vector<int> &v, vector<vector<int>> &dp) {
    if (i == j) return 0;
    if (dp[i][j] != INT_MAX) return dp[i][j];
    for (int k = i; k < j; k++) dp[i][j] = min(dp[i][j], matrixChainMultiplication(i, k, v, dp) + matrixChainMultiplication(k+1, j, v, dp) + v[i-1]*v[k]*v[j]);
    return dp[i][j];
}

int main() {
    int n; cin >> n;
    vector<int> v(n);
    vector<vector<int>> dp(n, vector<int> (n, INT_MAX));

    for (int i = 0; i < n; i++) cin >> v[i];

    cout << matrixChainMultiplication(1, n-1, v, dp) << endl;

    return 0;
}
