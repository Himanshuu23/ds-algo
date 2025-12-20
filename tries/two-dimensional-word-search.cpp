#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    unordered_map<char, TrieNode*> mp;
    bool endOfWord = false;
};

class Trie {
    public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }

    void insert(const string &word) {
        TrieNode* current = root;
        for (auto ch : word) {
            if (current->mp.find(ch) == current->mp.end()) current->mp[ch] = new TrieNode();
            current = current->mp[ch];
        }
        current->endOfWord = true;
    }

    TrieNode* find(char character, TrieNode* parent) {
        return (parent->mp.find(character) != parent->mp.end()) ? parent->mp[character] : nullptr;
    }

    void dfs(int i, int j, int M, int N, TrieNode* node, vector<vector<char>> &grid, string &current, vector<vector<int>> &visited, vector<string> &result) {
        if (i < 0 || j < 0 || i >= M || j >= N) return;
        if (visited[i][j]) return;
        
        char character = grid[i][j];
        TrieNode* child = find(character, node);
        if (!child) return;

        current.push_back(character);
        if (child->endOfWord) {
            result.push_back(current);
            child->endOfWord = false;
        }

        visited[i][j] = 1;
        
        dfs(i, j-1, M, N, child, grid, current, visited, result);
        dfs(i-1, j, M, N, child, grid, current, visited, result);
        dfs(i, j+1, M, N, child, grid, current, visited, result);
        dfs(i+1, j, M, N, child, grid, current, visited, result);

        visited[i][j] = 0;
        current.pop_back();
    }
};

int main() {
    Trie trie;
    vector<string> words = {"oath", "pea", "eat", "rain"};

    for (auto &w : words)
        trie.insert(w);

    vector<vector<char>> grid = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };

    int M = grid.size(), N = grid[0].size();
    vector<vector<int>> visited(M, vector<int>(N, 0));
    vector<string> result;
    string current = "";

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            trie.dfs(i, j, M, N, trie.root, grid, current, visited, result);
        }
    }

    for (auto &s : result)
        cout << s << endl;

    return 0;
}
