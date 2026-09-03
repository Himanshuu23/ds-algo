#include <bits/stdc++.h>
using namespace std;

// using dsu - O(V)
class DSU {
public:
    vector<int> parent, size;
    
    DSU (int n) {
        parent.resize(n);
        size.assign(n, 1);
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

        if (size[rootX] < size[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    }
};

// using dfs - O(V + E)
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        DSU dsu(n * m);

        auto index = [m](int i, int j) {
            return i * m + j;
        };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 1) continue;

                if (i + 1 < n && grid[i+1][j] == 1) {
                    dsu.unite(index(i, j), index(i + 1, j));
                }

                if (j + 1 < m && grid[i][j+1] == 1) {
                    dsu.unite(index(i, j), index(i, j + 1));
                }
            }
        }

        set<int> islands;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] != 1) continue;

                islands.insert(dsu.find(index(i, j)));
            }
        }

        int answer = 0;
        for (int island : islands) {
            answer = max(answer, dsu.size[island]);
        }

        return answer;
    }
};

class Solution2 {
private:
    vector<vector<bool>> visited;
    int n, m;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int dfs(vector<vector<int>>& grid, int i, int j) {
        visited[i][j] = true;
        int area = 1;

        for (auto [dx, dy] : directions) {
            int ni = i + dx, nj = j + dy;
            if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] == 1 && !visited[ni][nj]) {
                area += dfs(grid, ni, nj);
            }
        }

        return area;
    }

public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        visited.resize(n, vector<bool> (m, false));

        int area = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    area = max(area, dfs(grid, i, j));
                }
            }
        }

        return area;
    }
};

// using bfs - O(V + E)
class Solution3 {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool> (m, false));
        int answer = 0;

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] && !visited[i][j]) {
                    queue<pair<int, int>> q;
                    int area = 1;
                    q.push({i, j});
                    visited[i][j] = true;
                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        for (auto [dx, dy] : directions) {
                            int ni = x + dx, nj = y + dy;
                            if (ni >= 0 && nj >= 0 && ni < n && nj < m && grid[ni][nj] && !visited[ni][nj]) {
                                ++area;
                                q.push({ni, nj});
                                visited[ni][nj] = true;
                            }
                        }
                    }
                    answer = max(answer, area);
                }
            }
        }

        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
