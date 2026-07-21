#include<bits/stdc++.h>
using namespace std;

int solve(int n, int m, int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& dp) {
	if (i >= n || j >= m || j < 0) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	return dp[i][j] = matrix[i][j] + max({solve(n, m, i+1, j-1, matrix, dp), solve(n, m, i+1, j, matrix, dp), solve(n, m, i+1, j+1, matrix, dp)});
}

int main() {
    int N, M; cin >> N >> M;
    vector<vector<int>> v(N, vector<int> (M));
    vector<vector<int>> dp(N, vector<int> (M, -1));

    for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                cin >> v[i][j];

    int ans = INT_MIN;
    for (int j = 0; j < M; j++)
        ans = max(ans, solve(N, M, 0, j, v, dp));

    cout << ans << endl;

    return 0;
}
