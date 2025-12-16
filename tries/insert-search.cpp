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
        TrieNode* cur = root;

        for (char c : word) {
            if (cur->mp.find(c) == cur->mp.end()) {
                cur->mp[c] = new TrieNode();
            }
            cur = cur->mp[c];
        }
        cur->endOfWord = true;
    }

    bool search(const string &word) {
        TrieNode* cur = root;

        for (char c : word) {
            if (cur->mp.find(c) == cur->mp.end()) return false;
            cur = cur->mp[c];
        }
        return cur->endOfWord;
    }

    bool startsWith(const string &word) {
        TrieNode* cur = root;

        for (char c : word) {
            if (cur->mp.find(c) == cur->mp.end()) return false;
            cur = cur->mp[c];
        }
        return true;
    }
};

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("banana");

    cout << boolalpha;
    cout << trie.search("apple") << endl;
    cout << trie.search("app") << endl;

    cout << trie.startsWith("app") << endl;
    cout << trie.startsWith("ban") << endl;

    return 0;
}
