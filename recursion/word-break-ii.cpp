#include<bits/stdc++.h>
using namespace std;

// using backtracking - O(m + n*2^n) - for each character of string s (size n) we have two choices - take or don't take and also for copying strings and sentences -> length of the sentence m also time taken O(m)
// space = O(m + 2^n)
class Solution {
private:
    unordered_map<string, int> dictionary;
    vector<string> result;

    void backtrack(int i, string& s, string& word, string& sentence) {
        if (i == s.size()) {
            if (dictionary.find(word) != dictionary.end()) {
                if (!sentence.empty()) sentence += " ";
                sentence += word;
                result.push_back(sentence);
            }
            return;
        }

        if (dictionary.find(word) != dictionary.end()) {
            string oldWord = word;
            string oldSentence = sentence;

            if (!sentence.empty()) {
                sentence += " ";
            }
            sentence += word;
            word = "";

            backtrack(i, s, word, sentence);

            word = oldWord;
            sentence = oldSentence;
        }

        word += s[i];
        backtrack(i + 1, s, word, sentence);
    }

public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        for (string word : wordDict) {
            dictionary[word]++;
        }
        string sentence, word;

        backtrack(0, s, word, sentence);

        return result;
    }
};

// pruning above solution using tries : currently we're exploring substrings that can't even form a word - using trie we traverse word by word prefixes and as soon as we find prefix that cannot form a word anymore - then we don't have to search further - break early - same time and same complexity
// we can also do this using bottom up dp
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool endOfWord = false;
};

class Trie {
    public:
        TrieNode *root;

        Trie() {
            root = new TrieNode();
        }

        void addWord(const string& word) {
            TrieNode* current = root;
            for (char c : word) {
                if (!current->children.count(c)) {
                    current->children[c] = new TrieNode();
                }
                current = current->children[c];
            }
            current->endOfWord = true;
        }
};

class Solution2 {
private:
    vector<string> result;
    void backtrack(int i, string& s, vector<string>& path, Trie& trie) {
        if (i == s.size()) {
            string sentence;
            for (string word : path) {
                sentence += word + " ";
            }
            sentence.pop_back(); // removing the last space
            result.push_back(sentence);
            return;
        }

        TrieNode* node = trie.root;
        string word;
        for (int j = i; j < s.size(); j++) {
            char c = s[j];
            if (!node->children.count(c)) break;

            word.push_back(c);
            node = node->children[c];

            if (node->endOfWord) {
                path.push_back(word);
                backtrack(j + 1, s, path, trie);
                path.pop_back();
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        Trie trie;
        for (string word : wordDict) {
            trie.addWord(word);
        }

        vector<string> path;
        backtrack(0, s, path, trie);
        return result;
    }
};

// using dp - since many suffix that we reach to also are being recalculating so we can use dp for that - top down
// same complexities
class Solution3 {
private:
    unordered_set<string> dictionary;
    unordered_map<int, vector<string>> cache;

    vector<string> backtrack(string& s, int i) { // returns sentences that can be formed using string (i...n)
        if (i == s.size()) {
            return {""};
        }

        if (cache.count(i)) {
            return cache[i];
        }

        vector<string> result;
        for (int j = i; j < s.size(); j++) {
            string word = s.substr(i, j - i + 1);
            if (!dictionary.count(word)) {
                continue;
            }
            vector<string> strings = backtrack(s, j + 1);
            for (string substr : strings) {
                string sentence = word;
                if (!substr.empty()) {
                    sentence += " " + substr;
                }
                result.push_back(sentence);
            }
        }
        cache[i] = result;
        return result;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        for (string word : wordDict) {
            dictionary.insert(word);
        }
        return backtrack(s, 0);
    }
};

// combining above two approach for prefix (using tries) + suffix (using dp) optimizations
// same complexities
struct TrieNode2 {
    unordered_map<char, TrieNode2*> children;
    bool endOfWord = false;
};

class Trie2 {
    public:
        TrieNode2* root;

        Trie2() {
            root = new TrieNode2();
        }

        void addWord(string word) {
            TrieNode2* current = root;
            for (char c : word) {
                if (!current->children.count(c)) {
                    current->children[c] = new TrieNode2();
                }
                current = current->children[c];
            }
            current->endOfWord = true;
        }
};

class Solution4 {
private:
    unordered_map<int, vector<string>> cache;

    vector<string> backtrack(int i, string& s, Trie2& trie) {
        if (i == s.size()) {
            return {""};
        }

        if (cache.count(i)) {
            return cache[i];
        }

        vector<string> result;
        TrieNode2* current = trie.root;

        for (int j = i; j < s.size(); j++) {
            char c = s[j];
            if (!current->children.count(c)) {
                break;
            }

            current = current->children[c];
            if (current->endOfWord) {
                vector<string> strings = backtrack(j + 1, s, trie);
                for (string suffix : strings) {
                    string sentence = s.substr(i, j - i + 1);
                    if (!suffix.empty()) {
                        sentence += " " + suffix;
                    }
                    result.push_back(sentence);
                }
            }
        }

        return cache[i] = result;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        Trie2 trie;
        for (string word : wordDict) {
            trie.addWord(word);
        }

        return backtrack(0, s, trie);
    }
};
