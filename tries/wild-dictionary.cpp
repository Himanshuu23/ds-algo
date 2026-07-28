#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    unordered_map<char, TrieNode*> map;
    bool endOfWord = false;
};

class Trie {
    private:
    TrieNode* root;

    public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string &word) {
        TrieNode* current = root;
        for (char character : word) {
            if (current->map.find(character) == current->map.end())
                current->map[character] = new TrieNode();
            current = current->map[character];
        }
        current->endOfWord = true;
    }
};

int main() {
    return 0;
}
