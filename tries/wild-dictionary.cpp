#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    unordered_map<char, TrieNode*> children;
    bool endOfWord = false;
};

class WordDictionary {
public:
    TrieNode* root;

    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* current = root;

        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->endOfWord = true;
    }

    bool search_helper(TrieNode* current, int i, string& word) {
        if (i == word.size()) {
            return current->endOfWord;
        }

        char c = word[i];

        if (c != '.') {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            return search_helper(current->children[c], i + 1, word); // move to next child
        }

        // current character is '.' -> we need to explore all the children and also we have to start in the remaining substring from current trie node and not from root
        for (auto& [ch, child] : current->children) {
            if (search_helper(child, i + 1, word)) {
                return true;
            }
        }

        return false;
    }
    
    bool search(string word) {
        return search_helper(root, 0, word);
    }
};
