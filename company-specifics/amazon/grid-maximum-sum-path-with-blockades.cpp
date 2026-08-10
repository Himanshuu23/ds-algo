#include <bits/stdc++.h>
using namespace std;

/*
You are given an $M \times N$ matrix grid containing integers. You start at the top-left cell (0, 0) and want to reach the bottom-right cell (M - 1, N - 1).Movement & Rules:From any cell (r, c), you can only move Right (r, c + 1) or Down (r + 1, c).Roadblocks: Any cell with a negative value (grid[r][c] < 0) is blocked and cannot be stepped on.If grid[0][0] or grid[M - 1][N - 1] is negative, no valid path exists.Task:Return the maximum path sum from (0, 0) to (M - 1, N - 1). If no valid path exists, return -1.Sample CasePlaintextInput: grid = [
  [ 5,  3, -1],
  [ 2, -1,  4],
  [ 1,  8,  2]
]

Output: 18
Explanation:
- Valid path: (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2)
- Sum: 5 + 2 + 1 + 8 + 2 = 18.
- Note: Cells with -1 act as walls/obstacles and are avoided.
Link : https://leetcode.com/discuss/post/6414650/amazon-sde-1-interview-experience-februa-k70a/
*/

// O(M*N), O(M*N) -> -1 when path doesn't exists and -2 when dp not memoized yet
int solve(int i, int j, int M, int N, vector<vector<int>>& grid, vector<vector<int>>& dp) {
    if (i >= M || j >= N || grid[i][j] < 0) return -1;
    if (i == M - 1 && j == N - 1) return grid[i][j];
    if (dp[i][j] != -2) return dp[i][j];

    int down = solve(i + 1, j, M, N, grid, dp);
    int right = solve(i, j + 1, M, N, grid, dp);

    int bestNext = max(down, right);
    if (bestNext == -1) return dp[i][j] = -1;

    return dp[i][j] = grid[i][j] + bestNext;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int M, N; cin >> M >> N;
        vector<vector<int>> grid(M, vector<int>(N));
        vector<vector<int>> dp(M, vector<int>(N, -2));

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cin >> grid[i][j];
            }
        }

        int answer = solve(0, 0, M, N, grid, dp);
        cout << answer << '\n';
    }

    return 0;
}
