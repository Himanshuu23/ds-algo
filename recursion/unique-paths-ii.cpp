#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve(int i, int j, int m, int n, vector<vector<int>>& obstacleGrid, int& answer) {
        if (i < 0 || j < 0 || i >= m || j >= n || obstacleGrid[i][j]) return;

        if (i == m-1 && j == n-1) {
            ++answer;
            return;
        }

        solve(i+1, j, m, n, obstacleGrid, answer);
        solve(i, j+1, m, n, obstacleGrid, answer);
    }
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int answer = 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        solve(0, 0, m, n, obstacleGrid, answer);

        return answer;
    }
};

// dp solution
class Solution {
public:
    int solve(int rows, int cols, int r, int c, vector<vector<int>> &dp, vector<vector<int>>& obstacleGrid) {
    if (r >= rows || c >= cols || obstacleGrid[r][c]) return 0;
    if (r == rows-1 && c == cols-1) return 1;
    if (dp[r][c] != -1) return dp[r][c];

    return dp[r][c] = solve(rows, cols, r+1, c, dp, obstacleGrid) + solve(rows, cols, r, c+1, dp, obstacleGrid);
}

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m+1, vector<int> (n, -1));
        return solve(m, n, 0, 0, dp, obstacleGrid);
    }
};
