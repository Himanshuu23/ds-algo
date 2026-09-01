/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<vector<string>> BoardList;

// brute force - O(n! * n^2), O(n^2) - since for each row we have n choices to place the queens so overall n! and n^2 for checking if we can place
bool canPlace(int i, int j, vector<vector<char>>& answer) {
    for (int row = 0; row < answer.size(); row++) {
        for (int col = 0; col < answer[0].size(); col++) {
            if (answer[row][col] == 'Q') {
                if (col == j) return false;
                if (abs(row-i) == abs(col-j)) return false; // same diagonals check - since for a diagonal (row_index + col_index = n) remains constant
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

// same above solution O(n!) - we're not making those extra n^2 checks as below
class Solution {
private:
    vector<bool> cols, diagonal1, diagonal2;
    vector<vector<string>> result;

    void solve(int row, int n, vector<string>& board) {
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (cols[col] || diagonal1[row + col] || diagonal2[row - col + n - 1]) continue; // diagonal2 is at row - col just it doesn't becomes negative we add n - 1 to it

            board[row][col] = 'Q';
            cols[col] = diagonal1[row + col] = diagonal2[row - col + n - 1] = true; 

            solve(row + 1, n, board);

            board[row][col] = '.';
            cols[col] = diagonal1[row + col] = diagonal2[row - col + n - 1] = false; 
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        cols.resize(n, false);
        diagonal1.resize(2*n-1, false);    
        diagonal2.resize(2*n-1, false);
        vector<string> board(n, string(n, '.'));  
    
        solve(0, n, board);

        return result;
    }
};

// same way as above - bit masking optimization - since integers would be faster than using maps, sets and less memory being used
class Solution {
private:
    int column = 0, principal_diagonal = 0, off_diagonal = 0;
    vector<string> board;
    vector<vector<string>> result;

    void backtrack(int row, int n) {
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if ((column & (1 << col)) || principal_diagonal & (1 << (row + col)) || (off_diagonal & (1 << (row - col + n)))) { // above off_diagonal was index of array that's why it was row - col + n - 1
                continue;
            }

            column ^= (1 << col);
            principal_diagonal ^= (1 << (row + col));
            off_diagonal ^= (1 << (row - col + n));
            board[row][col] = 'Q';

            backtrack(row + 1, n);

            column ^= (1 << col);
            principal_diagonal ^= (1 << (row + col));
            off_diagonal ^= (1 << (row - col + n));
            board[row][col] = '.';
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        board.resize(n, string(n, '.'));

        backtrack(0, n);

        return result;    
    }
};

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
