#include<bits/stdc++.h>
using namespace std;

// brute force: using recursion - from each box in the grid - trying to find the word in all four directions
// time complexity - O(w * m * n * 4 * 3^(t - 1)) - w are the total words, m -> rows, n -> cols, t -> max length of a word. Now for each word -> max recursion calls would be 't' -> length deep. Now suppose we choose some character then we mark that cell as visited means for the next character we cannot go in that direction hence only for 1st character we have four directions to explore while for the remaining (t-1) we have 3 directions to explore.
class Solution {
public:
    int ROWS, COLS;

    bool dfs(vector<vector<char>>& board, string& word, int r, int c, int i) {
        if (i == word.length()) {
            return true;
        }

        if (r >= ROWS || r < 0 || c >= COLS || c < 0 || board[r][c] == '#' || board[r][c] != word[i]) {
            return false;
        }

        board[r][c] = '#';
        bool result = dfs(board, word, r + 1, c, i + 1) || dfs(board, word, r - 1, c, i + 1) || dfs(board, word, r, c + 1, i + 1) || dfs(board, word, r, c - 1, i + 1);
        board[r][c] = word[i];

        return result;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        ROWS = board.size();
        COLS = board[0].size();

        vector<string> result;

        for (string word : words) {
            bool found = false;
            for (int i = 0; i < ROWS && !found; i++) {
                for (int j = 0; j < COLS && !found; j++) {
                    if (board[i][j] != word[0]) continue;
                    if (dfs(board, word, i, j, 0)) {
                        result.push_back(word);
                        found = true;
                        break;
                    }
                }
            }
        }

        return result;
    }
};

// optimization: instead of traversing each word and doing same dfs every time which is repeating - searching all words together using trie -> O(m * n * 4 * 3^(t-1) + s), O(t)
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool endOfWord = false;
};

class Trie {
    public:
        TrieNode* root;

        Trie() {
            root = new TrieNode();
        }

        void addWord(const string& word) {
            TrieNode* current = root;

            for (char c : word) {
                if (current->children.find(c) == current->children.end()) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
            }
            current->endOfWord = true;
        }
};

class Solution2 {
private:
    int ROWS, COLS;
    unordered_set<string> result; // to avoid pushing the same word again

    void dfs(vector<vector<char>>& board, string& word, int r, int c, TrieNode* node) {
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] == '#' || !node->children.count(board[r][c])) {
            return;
        }

        word += board[r][c];
        node = node->children[board[r][c]];
        board[r][c] = '#';
    
        if (node->endOfWord) {
            result.insert(word);
        }

        dfs(board, word, r + 1, c, node);
        dfs(board, word, r - 1, c, node);
        dfs(board, word, r, c + 1, node);
        dfs(board, word, r, c - 1, node);

        board[r][c] = word.back();
        word.pop_back();
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for (const string& word : words) {
            trie.addWord(word);
        }

        ROWS = board.size(), COLS = board[0].size();
        
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                string word = "";
                dfs(board, word, r, c , trie.root);
            }
        }

        return vector<string> (result.begin(), result.end());
    }
};

// more optimization/pruning: for each trie node storing refs: that is how many words down in it form a word, so we don't explore nodes that we have already explored all the nodes for -> its refs would become 0 -> node is dead we don't explore it unnecessarily
struct TrieNode2 {
    unordered_map<char, TrieNode2*> children;
    int refs = 0;
    bool endOfWord = false;
};

class Trie2 {
    public:
        TrieNode2* root;

        Trie2() {
           root = new TrieNode2(); 
        }

        void addWord(const string& word) {
            TrieNode2* current = root;
            current->refs++;

            for (char c : word) {
                if (!current->children.count(c)) {
                    current->children[c] = new TrieNode2();
                }
                current = current->children[c];
                current->refs++;
            }
            current->endOfWord = true;
        }
};

class Solution3 {
    private:
        int ROWS, COLS;
        vector<string> result;

        int dfs(vector<vector<char>>& board, TrieNode2* node, int r, int c, string& word) {
            if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] == '#' || !node->children.count(board[r][c])) {
                return 0;
            }

            char ch = board[r][c];

            TrieNode2* previous = node;
            node = node->children[ch];

            board[r][c] = '#';
            word += ch;

            int found = 0;

            if (node->endOfWord) {
                result.push_back(word);
                node->endOfWord = false;
                found++;
            }

            found += dfs(board, node, r + 1, c, word);
            found += dfs(board, node, r - 1, c, word);
            found += dfs(board, node, r, c + 1, word);
            found += dfs(board, node, r, c - 1, word);

            board[r][c] = ch;
            word.pop_back();

            node->refs -= found; // remove the words that have been found
            
            // mark this branch as dead
            if (node->refs == 0) {
                previous->children.erase(ch);
            }

            return found;
        }

    public:
        vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
            ROWS = board.size();
            COLS = board[0].size();

            Trie2 trie;

            for (const string& word : words) {
                trie.addWord(word);
            }

            string word = "";

            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    dfs(board, trie.root, r, c, word);
                }
            }

            return result;
        }
};
