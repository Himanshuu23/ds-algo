#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    unordered_map<char, TrieNode*> mp;
    bool endOfWord;
};

class Trie {
    TrieNode* root;

    public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string &word) {
        TrieNode* curr = root;
        for (auto c : word) {
            if (curr->mp.find(c) == curr->mp.end())
                curr->mp[c] = new TrieNode();
            curr = curr->mp[c];
        }
        curr->endOfWord = true;
    }

    bool search(const string &word) {
        TrieNode* curr = root;
        for (auto c : word) {
            if (curr->mp.find(c) == curr->mp.end()) return false;
            curr = curr->mp[c];
        }
        return curr->endOfWord; 
    }

    bool startsWith(const string &word) {
        TrieNode* curr = root;
        for (auto c : word) {
            if (curr->mp.find(c) == curr->mp.end()) return false;
            curr = curr->mp[c];
        }
        return true; 
    }

    void trieDFS(TrieNode* node, string &current, vector<string> &result) {
        if (node->endOfWord) result.push_back(current);
        for (auto &p : node->mp) {
            current.push_back(p.first);
            trieDFS(p.second, current, result);
            current.pop_back();
        }
    }

    vector<string> autoComplete(string prefix) {
        TrieNode* curr = root;
        for (auto c : prefix) {
            if (curr->mp.find(c) == curr->mp.end()) return {};
            curr = curr->mp[c];
        }

        vector<string> res;
        string current = prefix;
        trieDFS(curr, current, res);
        
        return res;
    }
};

int main() {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");
    trie.insert("cart");

    const string prefix = "ca";
    vector<string> ans = trie.autoComplete(prefix);
    for (auto c : ans) cout << c << endl;

    return 0;
}
