#include <bits/stdc++.h>
using namespace std;

// using backtracking - O(m*n*4^(m*n)), O(m*n)
class Solution {
private:
    int n, m;
    bool pacific, atlantic;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(vector<vector<int>>& heights, int i, int j) {
        if (i == 0 || j == 0) {
            pacific = true;
        }

        if (i == n - 1 || j == m - 1) {
            atlantic = true;
        }

        int temp = heights[i][j];
        heights[i][j] = INT_MAX; // avoiding revisiting same cell again/infinite cycles
        for (auto [dx, dy] : directions) {
            int r = i + dx, c = j + dy;
            if (r >= 0 && c >= 0 && r < n && c < m && heights[r][c] <= temp) {
                dfs(heights, r, c);
            }

            if (pacific && atlantic) {
                break;
            }
        }

        heights[i][j] = temp;
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        n = heights.size(), m = heights[0].size();
        vector<vector<int>> result;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pacific = false, atlantic = false;
                dfs(heights, i, j);

                if (pacific && atlantic) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};

// using dfs - for not revisiting same cells again : reversing the thinking instead of going that what cells can lead the water to the oceans, going opposite way if water can go from ocean to that cell means it can go other way down as well so marking all the cells in the way in one go - now DFS isn't being called for each grid again and again!
// O(m*n), O(m*n)
class Solution2 {
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void dfs(vector<vector<int>>& heights, int i, int j, vector<vector<bool>>& ocean) {
        ocean[i][j] = true;
        for (auto [dx, dy] : directions) {
            int x = i + dx, y = j + dy;
            if (x >= 0 && y >= 0 && x < n && y < m && !ocean[x][y] && heights[x][y] >= heights[i][j]) {
                dfs(heights, x, y, ocean);
            }
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        n = heights.size(), m = heights[0].size();

        vector<vector<bool>> pacific(n, vector<bool> (m, false));
        vector<vector<bool>> atlantic(n, vector<bool> (m, false));

        for (int i = 0; i < m; i++) {
            dfs(heights, 0, i, pacific); // first row, all columns
            dfs(heights, n - 1, i, atlantic); // last row, all columns
        }

        for (int i = 0; i < n; i++) {
            dfs(heights, i, 0, pacific); // first col, all rows
            dfs(heights, i, m - 1, atlantic); // last col, all rows
        }

        vector<vector<int>> result;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};

// using bfs -> same idea O(m*n), O(m*n)
class Solution3 {
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    void bfs(vector<vector<int>>& heights, vector<vector<bool>>& ocean, queue<pair<int, int>>& q) {
        while (!q.empty()) {
            auto [r, c] = q.front();
            ocean[r][c] = true;
            q.pop();

            for (auto [dx, dy] : directions) {
                int x = r + dx, y = c + dy;

                if (x >= 0 && y >= 0 && x < n && y < m && !ocean[x][y] && heights[x][y] >= heights[r][c]) {
                    q.push({x, y});
                }
            }
        }
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        n = heights.size(), m = heights[0].size();

        vector<vector<bool>> pacific(n, vector<bool> (m, false));
        vector<vector<bool>> atlantic(n, vector<bool> (m, false));

        queue<pair<int, int>> pacificQueue, atlanticQueue;

        for (int i = 0; i < m; i++) {
            pacificQueue.push({0, i});
            atlanticQueue.push({n - 1, i});
        }

        for (int i = 0; i < n; i++) {
            pacificQueue.push({i, 0});
            atlanticQueue.push({i, m - 1});
        }

        bfs(heights, pacific, pacificQueue);
        bfs(heights, atlantic, atlanticQueue);
        
        vector<vector<int>> result;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};
