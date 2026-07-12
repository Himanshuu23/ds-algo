/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<string>> BoardList;

void solve(int row, int n, vector<string>& board, vector<bool>& cols, 
           vector<bool>& diag1, vector<bool>& diag2, BoardList& results) {
    if (row == n) {
        results.push_back(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (cols[col] || diag1[row + col] || diag2[row - col + n - 1])
            continue;

        board[row][col] = 'Q';
        cols[col] = diag1[row + col] = diag2[row - col + n - 1] = true;

        solve(row + 1, n, board, cols, diag1, diag2, results);

        // backtrack
        board[row][col] = '.';
        cols[col] = diag1[row + col] = diag2[row - col + n - 1] = false;
    }
}

// another solution
bool canPlace(int i, int j, vector<vector<char>>& answer) {
    for (int row = 0; row < answer.size(); row++) {
        for (int col = 0; col < answer[0].size(); col++) {
            if (answer[row][col] == 'Q') {
                if (col == j) return false;
                if (abs(row-i) == abs(col-j)) return false; // same diagonals check
            }
        }
    }
    return true;
}

void solve(int n, int i, vector<vector<char>>& answer) { // i -> current queens placed
    if (i == n) {
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                cout << answer[row][col] << " ";
            }
            cout << '\n';
        }
        cout << '\n';
        return;
    }
    for (int j = 0; j < n; j++) {
        if (canPlace(i, j, answer)) {
            answer[i][j] = 'Q';
            solve(n, i+1, answer);
            answer[i][j] = '.';
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false), diag1(2 * n - 1, false), diag2(2 * n - 1, false);
        BoardList results;

        solve(0, n, board, cols, diag1, diag2, results);

        cout << "Number of solutions: " << results.size() << "\n";
        for (const auto& solution : results) {
            for (const string& row : solution)
                cout << row << "\n";
            cout << "\n";
        }
    }

    return 0;
}
