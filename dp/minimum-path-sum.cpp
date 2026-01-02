#include<bits/stdc++.h>
using namespace std;

int findMinimumPathSum(int i, int j, int M, int N, vector<vector<int>>& v, vector<vector<int>>& dp) {
    if (i >= M || j >= N || i < 0 || j < 0) return 1e9;
    if (i == M-1 && j == N-1) return v[i][j];
    if (dp[i][j] != INT_MAX) return dp[i][j];

    return dp[i][j] = v[i][j] + min(findMinimumPathSum(i+1, j, M, N, v, dp), findMinimumPathSum(i, j+1, M, N, v, dp));
}
