#include<bits/stdc++.h>
using namespace std;

// if there is a land near a land then it removes its side for calculation for its area - hence non land cells adds up to area while land ones don't
// using dfs - O(n*m), O(n*m)
class Solution {
private:
    vector<vector<bool>> visited;

    int dfs(vector<vector<int>>& grid, int n, int m, int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= m || grid[i][j] == 0) {
            return 1;
        }

        if (visited[i][j]) {
            return 0;
        }

        visited[i][j] = true;
    
        return dfs(grid, n, m, i + 1, j) + dfs(grid, n, m, i - 1, j) + dfs(grid, n, m, i, j + 1) + dfs(grid, n, m, i, j - 1);
    }
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        visited.resize(n, vector<bool> (m, false));

        int answer = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j]) {
                    answer += dfs(grid, n, m, i, j);
                }
            }
        }

        return answer;
    }
};

// iterative method - O(n*m), O(1)
class Solution2 {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        int answer = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!grid[i][j]) continue;

                int area = 4;
                if (i + 1 < n && grid[i+1][j]) --area;
                if (i - 1 >= 0 && grid[i-1][j]) --area;
                if (j + 1 < m && grid[i][j+1]) --area;
                if (j - 1 >= 0 && grid[i][j-1]) --area;

                answer += area;
            }
        }

        return answer;
    }
};
