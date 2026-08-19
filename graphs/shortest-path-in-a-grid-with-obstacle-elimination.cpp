#include <bits/stdc++.h>
using namespace std;

// bfs -> to find the shortest distance, visited[i][j] = maximum remaining k seen so far at (i, j)
// manhattan distance = |x1 - x2| + |y1 - y2| now since we can move horizontally and vertically least moves required this way would be m + n but since indexing is 0 to m - 1 and 0 to n - 1 so we have m + n - 2 so if we have enough k to move this way then this is shortest possible path either way.
// Visit normally using bfs storing {i, j, remaining_k}, If we revisit the path (noting that bfs always provides shortest paths only first way, means earlier path had insufficient k's remaining so we revisit that path again only if we have more remaining_k than earlier else we fail either way coz it would be worse path than before + insufficient k_remaining
// O(m*n*k), O(m*n)
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
