#include<bits/stdc++.h>
using namespace std;

int findMaximumPathSum(int i, int j, int N, int M, vector<vector<int>> &v, vector<vector<int>> &dp) {
    if (i < 0 || i >= N || j < 0 || j >= M) return INT_MIN;
    if (i == N-1) return v[i][j];

    if (dp[i][j] != INT_MIN) return dp[i][j];

    return dp[i][j] = v[i][j] + max({findMaximumPathSum(i+1, j-1, N, M, v, dp), findMaximumPathSum(i+1, j, N, M, v, dp), findMaximumPathSum(i+1, j+1, N, M, v, dp)});
}

int main() {
    int N, M; cin >> N >> M;
    vector<vector<int>> v(N, vector<int> (M));
    vector<vector<int>> dp(N, vector<int> (M, INT_MIN));

    for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> v[i][j];

    int ans = INT_MIN;
    for (int j = 0; j < M; j++)
        ans = max(ans, findMaximumPathSum(0, j, N, M, v, dp));

    cout << ans << endl;

    return 0;
}
