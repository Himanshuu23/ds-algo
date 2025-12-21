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

    bool searchHelper(TrieNode* node, const string &word, int index) {
        if (!node) return false;
        if (index == word.size()) return node->endOfWord;

        char character = word[index];
        if (character == '.') {
            for (auto& p : node->map) {
                if (searchHelper(p.second, word, index + 1)) return true;
            }
            return false;
        } else {
            if (node->map.count(character) == 0) return false;
            return searchHelper(node->map[character], word, index + 1);
        }
    }

    bool removeHelper(TrieNode* node, const string &word, int index) {
        if (index == word.size()) {
            if (!node->endOfWord) return false;
            node->endOfWord = false;
            return node->map.empty();
        }

        char character = word[index];
        if (node->map.count(character) == 0) return false;

        bool shouldDeleteChild = removeHelper(node->map[character], word, index + 1);
        
        if (shouldDeleteChild) {
            delete node->map[character];
            node->map.erase(character);
            return node->map.empty() && !node->endOfWord;
        }

        return false;
    }

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

    bool search(const string &word) {
        return searchHelper(root, word, 0);
    }

    void remove(const string &word) {
        removeHelper(root, word, 0);
    }
};

int main() {
    Trie trie;
    trie.insert("add");
    trie.insert("and");
    trie.insert("apt");

    cout << trie.search("a.d") << endl;
    trie.remove("add");
    cout << trie.search("a.d") << endl;
    cout << trie.search("apt") << endl;

    return 0;
}
