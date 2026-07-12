/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;

vector<pair<int, int>> answer;
map<pair<int, int>, bool> visited;
vector<pair<int, int>> moves = { {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
               {-2, -1}, {-1, -2}, {1, -2}, {2, -1} };

bool bruteForce(int n, int x, int y, vector<pair<int, int>>& answer) { // solution without warnsdorffs
    if (x < 0 || y < 0 || x >= n || y >= n || visited[{x, y}]) return false;
    answer.push_back({x, y});
    visited[{x,y}] = true;
    if (answer.size() == n*n) return true;
    for (auto& [dx, dy] : moves) {
        if (bruteForce(n, x+dx, y+dy, answer)) return true;
    }
    answer.pop_back();
    visited[{x,y}] = false;

    return false;
}

vvi knight = { {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
               {-2, -1}, {-1, -2}, {1, -2}, {2, -1} };

int N;
bool finished = false;

vector<pair<int, int>> getPossiblePositions(int x, int y, vvi& visited) {
    vector<pair<int, int>> moves;
    for (auto& k : knight) {
        int nx = x + k[0], ny = y + k[1];
        if (nx >= 0 && ny >= 0 && nx < N && ny < N && visited[nx][ny] == -1) {
            moves.push_back({nx, ny});
        }
    }
    return moves;
}

void solve(int x, int y, int moveNum, vvi& visited, vvi& ans) {
    if (finished) return;

    visited[x][y] = moveNum;
    ans[moveNum][0] = x;
    ans[moveNum][1] = y;

    if (moveNum == N * N - 1) {
        finished = true;
        return;
    }

    auto moves = getPossiblePositions(x, y, visited);
    sort(moves.begin(), moves.end(), [&](pair<int, int>& a, pair<int, int>& b) {
        return getPossiblePositions(a.first, a.second, visited).size() <
               getPossiblePositions(b.first, b.second, visited).size();
    }); // sorting using Warnsdorffs rule - position that knight has fewer future moves available visit those first - reduces the chances of deadends - faster

    for (auto& move : moves) {
        solve(move.first, move.second, moveNum + 1, visited, ans);
        if (finished) return;
    }

    visited[x][y] = -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int x, y;
        cin >> N >> x >> y;

        vvi visited(N, vector<int>(N, -1));
        vvi ans(N * N, vector<int>(2));

        finished = false;
        solve(x, y, 0, visited, ans);

        if (finished) {
            for (auto& p : ans) {
                cout << "(" << p[0] << ", " << p[1] << ") ";
            }
            cout << "\n";
        } else {
            cout << "No solution found.\n";
        }
    }

    return 0;
}
