#include<bits/stdc++.h>
using namespace std;

// using backtracking + dfs (trying all four directions from each point on the board)
// If there are m cells in the board and word is n-sized O(m*4^n), O(n)
class Solution {
public:
    vector<vector<bool>> visited;
    int ROWS, COLS;

    bool dfs(vector<vector<char>>& board, string word, int r, int c, int i) {
        if (i == word.length()) {
            return true;
        }

        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] != word[i]  || visited[r][c]) {
            return false;
        }

        visited[r][c] = true;
        bool result = dfs(board, word, r + 1, c, i + 1) || dfs(board, word, r - 1, c, i + 1) || dfs(board, word, r, c + 1, i + 1) || dfs(board, word, r, c - 1, i + 1);
        visited[r][c] = false;

        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        ROWS = board.size();
        COLS = board[0].size();
        visited = vector<vector<bool>> (ROWS, vector<bool> (COLS, false));

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};

// we can remove the visited array as well
class Solution2 {
public:
    int ROWS, COLS;

    bool dfs(vector<vector<char>>& board, string word, int r, int c, int i) {
        if (i == word.length()) {
            return true;
        }

        if (r < 0 || c < 0 || r >= ROWS || c >= COLS || board[r][c] != word[i]  || board[r][c] == '#') {
            return false;
        }

        board[r][c] = '#';
        bool result = dfs(board, word, r + 1, c, i + 1) || dfs(board, word, r - 1, c, i + 1) || dfs(board, word, r, c + 1, i + 1) || dfs(board, word, r, c - 1, i + 1);
        board[r][c] = word[i];

        return result;
    }

    bool exist(vector<vector<char>>& board, string word) {
        ROWS = board.size();
        COLS = board[0].size();

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};
