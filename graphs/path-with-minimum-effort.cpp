#include <bits/stdc++.h>
using namespace std;

// we cannot use recursion + dp generally not used for four directions because in two direction movements grid behaves like a DAG, but here it might have cycles and infinite recursion and also with visited array then memoization wouldn't make sense like through one path we have visited the cell and saved answer in dp[i][j] but if through some other path we would have that cell not visited but we would be using dp[i][j] which is incorrect. Hence, generally recursion backtracking not used in four directions.

// this problem can be seen as a graph with weights as absolute difference between the heights and we have to find the path with shortest weight from (0, 0) to (n-1, m-1)
// Using dijkstra - O(m*n*log(m*n)), O(m*n)
// pushing (distance, row, col) in the minHeap and from current position going to all four directions comparing new height with current height and when we reach destination just return the distance.
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        vector<vector<int>> distance(n, vector<int> (m, INT_MAX)); // stores the best height till (r, c)
        distance[0][0] = 0;

        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        pq.push({0, 0, 0});

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();
            int difference = current[0], r = current[1], c = current[2];

            if (r == n - 1 && c == m - 1) return difference;
            if (distance[r][c] < difference) continue;

            for (auto [dx, dy] : directions) {
                int x = r + dx, y = c + dy;
                if (x < 0 || x >= n || y < 0 || y >= m) continue;

                int newDifference = max(difference, abs(heights[r][c] - heights[x][y]));
                if (newDifference < distance[x][y]) {
                    distance[x][y] = newDifference;
                    pq.push({ newDifference, x, y });
                }
            }
        }

        return 0;
    }
};

// binary search + dfs: as if a smaller value limit works then all values greater than it also work. Means we can binary search on the max height that works and try to minimize it. Finding a path that works with that limit value of the weight or height difference.
// O(m*n*log(maxHeightDifference)), O(m*n)
class Solution2 {
private:
    vector<vector<bool>> visited;
    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int n, m;

    bool dfs(vector<vector<int>>& heights, int r, int c, int limit) {
        if (r == n - 1 && c == m - 1) return true;

        visited[r][c] = true;
        for (auto& [dx, dy] : directions) {
            int x = r + dx, y = c + dy;

            if (x < 0 || y < 0 || x >= n || y >= m || visited[x][y]) continue;
            if (abs(heights[r][c] - heights[x][y]) > limit) continue;

            if (dfs(heights, x, y, limit)) {
                return true;
            }
        }

        return false;
    }
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        n = heights.size(), m = heights[0].size();
        visited.resize(n, vector<bool> (m, false));

        int l = 0, r = 1e6, answer = r;
        while (l <= r) {
            int limit = l + (r - l) / 2;
            for (auto& row : visited) {
                fill(row.begin(), row.end(), false);
            }
            if (dfs(heights, 0, 0, limit)) {
                answer = limit;
                r = limit - 1;
            } else {
                l = limit + 1;
            }
        }

        return answer;
    }
};

// using kruskal algorithm: as the problem is finding path with least weight from source to target. We can do it using kruskal. First making edges with "down" and "right" directions (enough to cover all the cells) when we do this for every cell it gets covered (no need for four directions). Then we can unite the edges in the DSU and also since we process the edges in sorted order of there weights we would only unite edges in sorted order and hence we always get the path with least height difference - basically we're building spanning tree (minimum). Now when we find first node that forms path from 0 to target: that would be the required answer since before it we would have connected nodes with weights less than current weight till now and hence this would be the absolute maxima of the path from source to destination.
// same complexity
class DSU {
private:
    vector<int> parent, _rank;
public:
    DSU (int n) : parent(n), _rank(n, 1) {
        iota(parent.begin(), parent.end(), 0);
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
};

class Solution3 {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();

        auto index = [m](int i, int j) {
            return i * m + j;
        };

        vector<tuple<int, int, int>> edges;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i + 1 < n) {
                    edges.push_back({abs(heights[i][j] - heights[i+1][j]), index(i, j), index(i+1, j)});
                }
                if (j + 1 < m) {
                    edges.push_back({abs(heights[i][j] - heights[i][j+1]), index(i, j), index(i, j + 1)});
                }
            }
        }
        
        sort(edges.begin(), edges.end());
        DSU dsu(n * m);
        int target = n * m - 1;

        for (auto& [w, u, v] : edges) {
            dsu.unite(u, v);
            if (dsu.find(0) == dsu.find(target)) return w;
        }

        return 0;
    }
};

// using spfa (shortest path faster algorithm): its bellman ford algo with queue optimization - a relaxation based shortest path algo just like dijkstra but simpler since it doesn't uses priority queue. dijkstra gurantees that first time if a node is popped its answer would be shortest but here that is not guranteed that tradeoff is done with simplicity. So, a node might be pushed more than one times. Just tracking distance[cell] = max height difference to go from 0 to that cell, we try all neighbors and update the answer if required i.e. if that's better and smaller and also pushing those neighbor into the queue - they might lead to optimizing their neighbors too.
// O(m*n) in average case, O(m^2 * n^2) in worst case, O(m*n) space
class Solution4 {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();

        auto index = [m](int i, int j) {
            return i * m + j;
        };

        vector<int> distance(n * m, INT_MAX);
        vector<bool> inQueue(n * m, false);
        distance[0] = 0;

        queue<pair<int, int>> q;
        q.push({0, 0});
        inQueue[0] = true;

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            inQueue[index(r, c)] = false;

            for (auto& [dr, dc] : directions) {
                int x = r + dr, y = c + dc;
                if (x < 0 || y < 0 || x >= n || y >= m) continue;

                int newEffort = max(distance[index(r, c)], abs(heights[r][c] - heights[x][y]));
                if (newEffort < distance[index(x, y)]) {
                    distance[index(x, y)] = newEffort;
                    if (!inQueue[index(x, y)]) {
                        q.push({x, y});
                        inQueue[index(x, y)] = true;
                    }
                }
            }
        }

        return distance[n * m - 1];
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
