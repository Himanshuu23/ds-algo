/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int i, int W, vector<int>& wt, vector<int>& val, vector<vector<int>>& dp) {
    if (i == wt.size()) return 0;
    if (dp[i][W] != -1) return dp[i][W];

    int exclude = solve(i+1,W,wt,val,dp);
    int include(0);
    if (wt[i] <= W) include = val[i] + solve(i+1,W-wt[i],wt,val,dp);
    return dp[i][W] = max(include, exclude);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, W; cin >> n >> W;
        vector<int> wt(n), val(n);
        for (int i = 0; i < n; i++) cin >> wt[i];
        for (int i = 0; i < n; i++) cin >> val[i];
        vector<vector<int>> dp(n+1, vector<int>(W + 1, -1));
        cout << solve(0, W, wt, val, dp) << endl;
    }

    return 0;
}
