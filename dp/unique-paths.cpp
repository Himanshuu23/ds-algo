/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int rows, int cols, int r, int c, vector<vector<int>> &dp) {
    if (r == rows-1 && c == cols-1) return 1;
    if (dp[r][c] != -1) return dp[r][c];

    int paths = 0;
    if (r+1 < rows) paths += solve(rows, cols, r+1, c, dp);
    if (c+1 < cols) paths += solve(rows, cols, r, c+1, dp);

    return dp[r][c] = paths;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int r, c; cin >> r >> c;
        vector<vector<int>> dp(r, vector<int> (c, -1));
        cout << solve(r, c, 0, 0, dp) << endl;
    }

    return 0;
}

class Solution {
public:
int solve(int i, int j, vector<vector<int>>& dp) {
    if (i < 0 || j < 0) return 0;
    if (i == 0 && j == 0) return 1;
    if (dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solve(i-1, j, dp) + solve(i, j-1, dp);
}

    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int> (n+1, -1));

        return solve(m-1, n-1, dp);
    }
};
