#include <bits/stdc++.h>
using namespace std;

// for a path the time is just the max grid[i][j] value since that is the max time node required to wait
// brute force dfs - O(4^n^2), O(n^2)
class Solution {
private:
    int n;
    vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    set<pair<int, int>> visited;

    int dfs(vector<vector<int>>& grid, int i, int j, int answer) {
        if (i < 0 || j < 0 || i >= n || j >= n || visited.count({i, j})) return INT_MAX;

        if (i == n - 1 && j == n - 1) {
            return max(answer, grid[i][j]);
        }

        visited.insert({i, j});
        int result = INT_MAX;
        answer = max(answer, grid[i][j]);
        for (auto [dx, dy] : directions) {
            result = min(result, dfs(grid, i + dx, j + dy, answer));
        }
        visited.erase({i, j});

        return result;
    }
    
public:
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();

        return dfs(grid, 0, 0, 0);
    }
};

// O(n^4), O(n^2) - for each value of "time" if the water level can be reached through the current value of "time" then that works we just have to find the minimum value of that. - hence for each just "yes" or "no" - since values that are being searched are n^2 - grid[0][0] smallest suppose to grid[n-1][n-1] largest
class Solution2 {
private:
    int n;
    set<pair<int, int>> visited;

    bool dfs(vector<vector<int>>& grid, int i, int j, int time) {
        if (i < 0 || j < 0 || i >= n || j >= n || visited.count({i, j}) || grid[i][j] > time) return false;

        if (i == n - 1 && j == n - 1) {
            return true;
        }

        visited.insert({i, j});
        return dfs(grid, i + 1, j, time) || dfs(grid, i - 1, j, time) || dfs(grid, i, j + 1, time) || dfs(grid, i, j - 1, time);
    }
public:
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();
        
        int minH = grid[0][0], maxH = grid[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minH = min(minH, grid[i][j]);
                maxH = max(maxH, grid[i][j]);
            }
        }

        for (int time = minH; time < maxH; time++) {
            if (dfs(grid, 0, 0, time)) {
                return time;
            }
            visited.clear();
        }

        return maxH;
    }
};

// binary search + dfs - O(n^2 logn) to find the value of the "time" just using binary search instead of linear search
class Solution3 {
private:
    int n;
    set<pair<int, int>> visited;

    bool dfs(vector<vector<int>>& grid, int i, int j, int time) {
        if (i < 0 || j < 0 || i >= n || j >= n || visited.count({i, j}) || grid[i][j] > time) return false;

        if (i == n - 1 && j == n - 1) {
            return true;
        }

        visited.insert({i, j});
        return dfs(grid, i + 1, j, time) || dfs(grid, i - 1, j, time) || dfs(grid, i, j + 1, time) || dfs(grid, i, j - 1, time);
    }
public:
    int swimInWater(vector<vector<int>>& grid) {
        n = grid.size();
        
        int minH = grid[0][0], maxH = grid[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minH = min(minH, grid[i][j]);
                maxH = max(maxH, grid[i][j]);
            }
        }

        int left = minH, right = maxH;
        while (left < right) {
            int middle = (left + right) >> 1;
            if (dfs(grid, 0, 0, middle)) {
                right = middle;
            } else {
                left = middle + 1;
            }
            visited.clear();
        }

        return right;
    }
};

// using dijkstra - O(n^2 logn) - we can look at this problem as finding the least cost path from (0, 0) to (n-1, n-1) where cost is max grid[i][j] value of the path - so we have to minimize that value
class Solution4 {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        set<pair<int, int>> visited;
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        pq.push({grid[0][0], 0, 0});
        visited.insert({0, 0});

        while (!pq.empty()) {
            auto current = pq.top(); pq.pop();
            int time = current[0], i = current[1], j = current[2];
            if (i == n - 1 && j == n - 1) {
                return time;
            }

            for (auto [dx, dy] : directions) {
                int x = i + dx, y = j + dy;
                if (x < 0 || y < 0 || x >= n || y >= n || visited.count({x, y})) {
                    continue;
                }
                visited.insert({x, y});
                pq.push({max(time, grid[x][y]), x, y});
            }
        }

        return -1;
    }
};

// using kruskal - O(n^2 logn) - finding the minimum time after which (0, 0) and (n-1, n-1) become part of the same connected component
class DSU {
    vector<int> parent, _rank;
    public:
        DSU(int n) : parent(n), _rank(n, 1) {
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
            
            if (rootX == rootY) return;
        
            if (_rank[rootX] < _rank[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            
            if (_rank[rootX] == _rank[rootY]) _rank[rootX]++;
        }

        bool connected(int x, int y) {
            return find(x) == find(y);
        }
};

class Solution5 {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        DSU dsu(n * n);
        vector<vector<int>> positions;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                positions.push_back({grid[i][j], i, j});
            }
        }

        sort(positions.begin(), positions.end());
        
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

        auto index = [n](int i, int j) {
            return i * n + j;
        };

        for (auto current : positions) {
            int time = current[0], i = current[1], j = current[2];
            for (auto [dx, dy] : directions) {
                int x = i + dx, y = j + dy;
                if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] > time) continue;
                dsu.unite(index(i, j), index(x, y));
            }
            if (dsu.connected(0, n * n - 1)) return time;
        }

        return -1;
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
