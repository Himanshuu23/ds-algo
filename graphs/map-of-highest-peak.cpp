#include<bits/stdc++.h>
using namespace std;

// multi source bfs - O(m*n), O(m*n)
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = isWater.size(), m = isWater[0].size();

        vector<vector<int>> height(n, vector<int> (m, -1));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (isWater[i][j]) {
                    height[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (auto [dx, dy] : directions) {
                int r = x + dx, c = y + dy;

                if (r >= 0 && c >= 0 && r < n && c < m && !isWater[r][c] && height[r][c] == -1) {
                    height[r][c] = 1 + height[x][y];
                    q.push({r, c});
                }
            }
        }

        return height;
    }
};
