#include<bits/stdc++.h>
using namespace std;

// similar to problem walls and gates

// using dfs + backtracking - find the minimum distance for each fresh orange to rotten orange and maximum distance is the required result. 
// O(m*n*4^(m*n)), O(m*n)
class Solution {
private:
    int n, m;
    vector<vector<bool>> visited;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int dfs(vector<vector<int>>& grid, int i, int j) {
        if (grid[i][j] == 2) {
            return 0;
        }

        if (grid[i][j] == 0) {
            return INT_MAX;
        }

        visited[i][j] = true;
    
        int result = INT_MAX;
        for (auto [dx, dy] : directions) {
            int x = i + dx, y = j + dy;
            if (x >= 0 && y >= 0 && x < n && y < m && !visited[x][y]) {
                int current = dfs(grid, x, y);
                if (current != INT_MAX) {
                    result = min(result, 1 + current);
                }
            }
        }

        visited[i][j] = false;
        return result;
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        visited.resize(n, vector<bool> (m, false));

        int answer = -1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    int current = dfs(grid, i, j);
                    if (current != INT_MAX) {
                        answer = max(answer, current);
                    }
                }
            }
        }

        return answer;
    }
};

// using bfs - O((m*n)^2), O(m*n) - each node in bfs traversal is reached by shortest path only so that is guranteed but issue in this is - some nodes are processed more than once - same idea as above
class Solution2 {
private:
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

    int bfs(vector<vector<int>>& grid, int i, int j) {
        vector<vector<bool>> visited(n, vector<bool> (m, false));
        queue<pair<int, int>> q;
        visited[i][j] = true;
        q.push({i, j});

        int steps = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();
                if (grid[x][y] == 2) return steps;

                for (auto [dx, dy] : directions) {
                    int pi = x + dx, pj = y + dy;

                    if (pi >= 0 && pj >= 0 && pi < n && pj < m && !visited[pi][pj] && grid[pi][pj] != 0) {
                        q.push({pi, pj});
                        visited[pi][pj] = true;
                    }
                }
            }
            steps++;
        }

        return INT_MAX;
    }
public:
    int orangesRotting(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();

        int answer = 0; // if all oranges are rotten no time
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    int current = bfs(grid, i, j);
                    if (current == INT_MAX) {
                        return -1; // there are oranges that are unreachable
                    } else {
                        answer = max(answer, current);
                    }
                }
            }
        }

        return answer;
    }
};

// multi source bfs - O(m*n), O(m*n)
class Solution3 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int fresh = 0;
        int time = 0;

        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == 1) {
                    fresh++;
                }
                if (grid[r][c] == 2) {
                    q.push({r, c});
                }
            }
        }

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (fresh > 0 && !q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                auto [x, y] = q.front();
                q.pop();

                for (auto [dx, dy] : directions) {
                    int row = x + dx, col = y + dy;
                    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size() && grid[row][col] == 1) {
                        grid[row][col] = 2;
                        q.push({row, col});
                        fresh--;
                    }
                }
            }
            time++;
        }

        return fresh == 0 ? time : -1;
    }
};

// O((m*n)^2), O(m*n) - bfs without queue
class Solution4 {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int fresh = 0;
        int time = 0;

        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == 1) {
                    fresh++;
                }
            }
        }

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        while (fresh > 0) {
            bool flag = false;
            for (int r = 0; r < grid.size(); r++) {
                for (int c = 0; c < grid[0].size(); c++) {
                    if (grid[r][c] == 2) {
                        for (auto [dx, dy] : directions) {
                            int row = r + dx, col = c + dy;
                            if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size() && grid[row][col] == 1) {
                                grid[row][col] = 3;
                                fresh--;
                                flag = true;
                            }
                        }
                    }
                }
            }

            if (!flag) return -1;

            for (int r = 0; r < grid.size(); r++) {
                for (int c = 0; c < grid[0].size(); c++) {
                    if (grid[r][c] == 3) grid[r][c] = 2;
                }
            }

            time++;
        }

        return time;
    }
};
