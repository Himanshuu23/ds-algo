#include <bits/stdc++.h>
using namespace std;

// backtracking - O(m*n*4^(n*m)), O(m*n) - exploring each '0' and doing dfs for it
class Solution {
private:
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited;
    
    bool dfs(vector<vector<char>>& board, int i, int j) {
        int count = 0;
        visited[i][j] = true;
        for (auto [dx, dy] : directions) {
            int x = i + dx, y = j + dy;
            if (x < 0 || y < 0 || x >= n || y >= m)  { // corners means '0' is free
                continue;
            } 

            if (board[x][y] == 'X' || visited[x][y]) { // cycled back to same cell or 'X' -> blocked
                ++count;
                continue;
            }

            count += dfs(board, x, y);
        }
        visited[i][j] = false;

        return (count == 4); // blocked in all four directions?
    }

public:
    void solve(vector<vector<char>>& board) {
        n = board.size(), m = board[0].size();
        visited.resize(n, vector<bool> (m, false));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O') {
                    if (dfs(board, i, j)) {
                        board[i][j] = 'X';
                    }
                }
            }
        }
    }
};

// optimization: avoiding making calls for all the cells - instead approach is using dfs - all the 'O' on the corners are safe and all the 'O' inside which are reachable from them are also same so just marking them as visited
// O(n*m), O(n*m)
class Solution2 {
private:
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited;

    void dfs(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= n || j >= m || visited[i][j] || board[i][j] == 'X') {
            return;
        }

        visited[i][j] = true;
        for (auto [dx, dy] : directions) {
            int x = i + dx, y = j + dy;
            dfs(board, x, y);
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        n = board.size(), m = board[0].size();
        visited.resize(n, vector<bool> (m, false));

        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O') {
                dfs(board, i, 0);
            }
            if (board[i][m-1] == 'O') {
                dfs(board, i, m - 1);
            }
        }

        for (int i = 0; i < m; i++) {
            if (board[0][i] == 'O') {
                dfs(board, 0, i);
            }
            if (board[n-1][i] == 'O') {
                dfs(board, n - 1, i);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O' && !visited[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

// using bfs - same idea - O(n*m), O(n*m)
class Solution3 {
private:
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    vector<vector<bool>> visited;
    
    void bfs(vector<vector<char>>& board, queue<pair<int, int>>& q) {
        while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();
            visited[i][j] = true;

            for (auto [dx, dy] : directions) {
                int x = i + dx, y = j + dy;
                if (x >= 0 && y >= 0 && x < n && y < m && !visited[x][y] && board[x][y] == 'O') {
                    visited[x][y] = true;
                    q.push({x, y});
                }
            }
        }
    }

public:
    void solve(vector<vector<char>>& board) {
        n = board.size(), m = board[0].size();
        visited.resize(n, vector<bool> (m, false));

        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O') {
                q.push({i, 0});
            }
            if (board[i][m-1] == 'O') {
                q.push({i, m - 1});
            }
        }
        for (int i = 0; i < m; i++) {
            if (board[0][i] == 'O') {
                q.push({0, i});
            }
            if (board[n-1][i] == 'O') {
                q.push({n-1, i});
            }
        }

        bfs(board, q);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O' && !visited[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
