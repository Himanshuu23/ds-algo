#include<bits/stdc++.h>
using namespace std;

class TrieNode {
    public:
    unordered_map<char, TrieNode*> map;
    bool endOfWord = false;
    int index;
};

bool isPalindrome(const string &word, int start, int end) {
    while(start < end) {
        if (word[start++] != word[end--]) return false;
    }
    return true;
}

string getRemaining(const string &word, int start, int n) {
    string ans;
    for (int i = start; i < n; i++) ans += word[i];
    return ans;
}

class Trie {
    public:
    TrieNode* root;

    Trie() {
        root = new TrieNode;
    }

    void insert(string word, int index) {
        TrieNode* current = root;
        
        for (int i = word.size()-1; i >= 0; i--) {
            if (current->map.find(word[i]) == current->map.end())
                current->map[word[i]] = new TrieNode();
            current = current->map[word[i]];
        }

        current->endOfWord = true;
        current->index = index;
    }

    int find(const string &word) {
        TrieNode* current = root;
        for (auto character : word) {
            if (current->map.find(character) == current->map.end()) return -1;
            current = current->map[character];
        }
        return (current->endOfWord) ? current->index : -1;
    }

void findPalindromicPair(const string &word, int index) {
    int n = word.size();
    for (int k = 0; k <= n; ++k) {
        string pref = getRemaining(word, 0, k);
        int idx = find(pref);
        if (idx != -1 && idx != index) {
            if (isPalindrome(word, k, n - 1)) {
                cout << index << " " << idx << endl;
            }
        }
    }
    for (int k = 1; k <= n; ++k) {
        if (isPalindrome(word, 0, k - 1)) {
            string suff = getRemaining(word, k, n);
            int idx = find(suff);
            if (idx != -1 && idx != index) {
                cout << idx << " " << index << endl;
            }
        }
    }
}
};

int main() {
    int n, idx; cin >> n;
    vector<string> v(n);
    Trie trie;
    
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        trie.insert(v[i], i);
    }

    for (int i = 0; i < n; i++)
        trie.findPalindromicPair(v[i], i);

    return 0;
}
