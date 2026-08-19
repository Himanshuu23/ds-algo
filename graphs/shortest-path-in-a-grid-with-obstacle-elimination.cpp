#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int M = grid.size(), N = grid[0].size();
            if (k >= M + N - 2) return M + N - 2;

    queue<tuple<int, int, int>> q;
    q.push({ 0, 0, k });

    vector<vector<int>> visited(M, vector<int> (N, -1));
    visited[0][0] = k;

    int moves = 0;
    int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    while (!q.empty()) {
        int size = q.size();

        while (size--) {
            auto [x, y, remaining_k] = q.front();
            q.pop();

            if (x == M - 1 && y == N - 1) return moves;

            for (auto& d : directions) {
                int nx = x + d[0];
                int ny = y + d[1];

                if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                    int next_k = remaining_k - grid[nx][ny];

                    if (next_k >= 0 && next_k > visited[nx][ny]) {
                        visited[nx][ny] = next_k;
                        q.push({nx, ny, next_k});
                    }
                }
            }
        }
        moves++;
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
