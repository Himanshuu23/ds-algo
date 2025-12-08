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
