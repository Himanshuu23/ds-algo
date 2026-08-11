#include <bits/stdc++.h>
using namespace std;

/*
You are given an $N \times M$ grid representing a city layout, where:1 represents an existing delivery center.0 represents a house (or empty cell).The inconvenience of any house located at cell $(x_1, y_1)$ is defined as the Chebyshev distance to its nearest delivery center at $(x_2, y_2)$, allowing 8-directional movement:$$\text{Distance} = \max(\vert{}x_1 - x_2\vert{}, \vert{}y_1 - y_2\vert{})$$The overall city inconvenience is defined as the maximum inconvenience across all houses in the grid.TaskYou are allowed to build at most one new delivery center at any available house location (cell with 0).Find the minimum possible overall city inconvenience after strategically placing at most one new delivery center.Constraints$1 \le N, M \le 500$Grid entries are strictly 0 or 1.If there are no houses in the grid, the inconvenience is 0.If there is already at least one delivery center, you may choose not to add a new one if it doesn't reduce the maximum inconvenience further.
Link - https://leetcode.com/discuss/post/8387183/amazon-oa-2026-by-anonymous_user-b5um/
*/

// brute force would be bfs all houses and marking those already visited since they first time get visited by the nearest center only. So we can do this for each delivery house in all directions and find the max distance while we visit each house but then checking whether placing new center on this (i, j) would be another (N*M) so overall O(N*M)^2
// We can simplify finding where to place instead does this value of K works for all houses and find the min value using binary search so O(N*Mlog(N*M))
// for each K -> there should be no violating houses i.e. houses whose distance from existing centers > K. to check just see if max(abs(r-x), abs(c-y)) is <= K where (r, c) is house position while (x, y) is center.
// For each violating house the best place to place center would be intersection of each + min distance from each -> $$x_{min} = \max(r_i - K), \quad x_{max} = \min(r_i + K)$$$$y_{min} = \max(c_i - K), \quad y_{max} = \min(c_i + K)$$

const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
int minInconvenience(int N, int M, vector<vector<int>>& grid) {
    vector<vector<int>> distance(N, vector<int> (M, -1));
    queue<pair<int, int>> q;

    // pushing all the centers
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 1) {
                distance[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    if (q.empty()) {
        return max(N, M) / 2;
    }

    int max_distance = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        max_distance = max(max_distance, distance[r][c]);
        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M && distance[nr][nc] == -1) {
                distance[nr][nc] = distance[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    
    auto canAchieveK = [&](int K) {
        int x_min = 0, x_max = N - 1;
        int y_min = 0, y_max = M - 1;
        bool has_violating_house = false;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (distance[i][j] > K) {
                    has_violating_house = true;

                    // intersection bounding boxes: [i-K, i+K] x [j-K, j+K]
                    x_min = max(x_min, i - K);
                    x_max = min(x_max, i + K);
                    y_min = max(y_min, j - K);
                    y_max = min(y_max, j + K);
                }
            }
        }

        if (!has_violating_house) {
            return true;
        }

        // checking if valid non empty overlapping region exists inside grid - we place on extra there
        return (x_min <= x_max) && (y_min <= y_max);
    };

    int low = 0, high = max_distance, answer = max_distance;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (canAchieveK(middle)) {
            answer = middle;
            high = middle - 1;
        } else low = middle + 1;
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        vector<vector<int>> grid(N, vector<int> (M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> grid[i][j];
            }
        }

        cout << minInconvenience(N, M, grid) << '\n';
    }

    return 0;
}
