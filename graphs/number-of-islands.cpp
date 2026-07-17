/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class DSU {
public:
    vector<int> parent, rank_;
    
    DSU (int n) {
        parent.resize(n);
        rank_.assign(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x), rootY = find(y);

        if (rootX == rootY) {
            return;
        }

        if (rank_[rootX] < rank_[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        if (rank_[rootX] == rank_[rootY]) rank_[rootX]++;
    }
};

int numIslandsDSU(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    DSU dsu(n*m);

    auto idx = [m](int i, int j) {
        return i * m + j;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != 1) continue;

            if (j + 1 < m && grid[i][j+1] == 1) {
                dsu.unite(idx(i, j), idx(i, j+1));
            }

            if (i + 1 < n && grid[i+1][j] == 1) {
                dsu.unite(idx(i, j), idx(i+1, j));
            }
        }
    }

    set<int> islands;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1) {
                islands.insert(dsu.find(idx(i, j)));
            }
        }
    }

    return islands.size();
}

void dfs(int i, int j, vector<vector<char>>& grid, vector<vector<bool>>& visited) {
    int n = grid.size(), m = grid[0].size();
    visited[i][j] = true;

    vector<pair<int, int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};
    for (auto [dx, dy] : dirs) {
        int ni = i + dx, nj = j + dy;
        if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] == '1' && !visited[ni][nj]) { // moving to each neighbor - if not visited and is 1 and unvisited then doing dfs on it
            dfs(ni, nj, grid, visited);
        }
    }
}

int countIslandsDFS(vector<vector<char>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                dfs(i, j, grid, visited);
                count++;
            }
        }
    }

    return count;
}

int countIslandsBFS(vector<vector<char>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int count = 0;

    vector<pair<int, int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                queue<pair<int, int>> q;
                q.push({i, j});
                visited[i][j] = true;

                while (!q.empty()) {
                    auto [x, y] = q.front(); q.pop();
                    for (auto [dx, dy] : dirs) {
                        int ni = x + dx, nj = y + dy;
                        if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] == '1' && !visited[ni][nj]) {
                            visited[ni][nj] = true;
                            q.push({ni, nj});
                        }
                    }
                }

                count++;
            }
        }
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        vector<vector<char>> grid = {
            {'1','1','0','0','0'},
            {'1','1','0','0','0'},
            {'0','0','1','0','0'},
            {'0','0','0','1','1'}
        };

        int result_dfs = countIslandsDFS(grid);
        cout << "DFS: Number of islands: " << result_dfs << endl;

        int result_bfs = countIslandsBFS(grid);
        cout << "BFS: Number of islands: " << result_bfs << endl;
    }

    return 0;
}
