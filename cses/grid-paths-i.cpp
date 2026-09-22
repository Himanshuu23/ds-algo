#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int solve(vector<string>& grid, int n, int i, int j, vector<vector<int>>& dp) {
    if (i < 0 || j < 0 || i >= n || j >= n || grid[i][j] == '*') return 0;
    if (i == n - 1 && j == n - 1) return 1;
    
    if (dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = (solve(grid, n, i + 1, j, dp) + solve(grid, n, i, j + 1, dp)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        vector<vector<int>> dp(n, vector<int> (n, -1));

        cout << (solve(grid, n, 0, 0, dp) % MOD) << '\n';
    }

    return 0;
}
