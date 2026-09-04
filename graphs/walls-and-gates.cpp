#include<bits/stdc++.h>
using namespace std;

// brute force dfs + backtracking - O(m*n*4^(m*n)), O(m*n)
class Solution {
private:
    vector<vector<bool>> visited;
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (grid[i][j] == -1) {
            return INT_MAX;
        }

        if (grid[i][j] == 0) {
            return 0;
        }

        visited[i][j] = true;
        
        int result = grid[i][j];
        for (auto [dx, dy] : directions) {
            int pi = i + dx, pj = j + dy;
            if (pi >= 0 && pj >= 0 && pi < n && pj < m && !visited[pi][pj]) {
                int current = dfs(grid, pi, pj);
                if (current != INT_MAX) { // adding 1 to INT_MAX will make it INT_MIN
                    result = min(result, 1 + current);
                }
            }
        }

        visited[i][j] = false; // since path of one node - can pass through some other already visited node so we can't mark it as visited forever and never visit again
        return result;
    }
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        visited.resize(n, vector<bool> (m, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == INT_MAX) {
                    grid[i][j] = dfs(grid, i, j);
                }
            }
        }
    }
};

// using bfs : best for shortest path in undirected graph. We expand for each node level by level and hence we're guranteed to get the shortest path to the '0'. But since we have to reset visited array coz for other nodes we might have path through some visited node so can't let it stay blocked forever. bfs calls would repeat for grid cells - since we're calling for each grid cells. O((m*n)^2), O(m*n)
class Solution2 {
private:
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int bfs(vector<vector<int>>& grid, int i, int j) {
        queue<pair<int, int>> q;
        q.push({ i, j });
        vector<vector<bool>> visited(n, vector<bool> (m, false));
        visited[i][j] = true;

        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [row, col] = q.front();
                q.pop();
                if (grid[row][col] == 0) return steps;

                for (auto [dx, dy] : directions) {
                    int nx = row + dx, ny = col + dy;
                    if (nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny] && grid[nx][ny] != -1) {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                }
            }
            steps++;
        }

        return INT_MAX;
    }
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == INT_MAX) {
                    grid[i][j] = bfs(grid, i, j);
                }
            }
        }
    }
};

// most optimal would be we start from each '0' and do bfs to find places we can visit through them - so we reach shortest one early and - we do multi source bfs - processing multiple '0' at the same time - O(m*n)
// Hence if answer to a node is precalculated means we have already processed that node - we don't need to know and hence no revisiting same nodes again and also if some path is through some other already visited node that also gets covered
class Solution3 {
public:
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (auto [dx, dy] : directions) {
                int r = row + dx, c = col + dy;

                if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == INT_MAX) {
                    grid[r][c] = 1 + grid[row][col];
                    q.push({r, c});
                }
            }
        }
    }
};
