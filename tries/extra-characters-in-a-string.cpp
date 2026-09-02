#include<bits/stdc++.h>
using namespace std;

// O(n*2^n + m*k) - for each 'n' characters of the string we have two choices - include or don't include it. Also while inserting into the set - total m words where k is the average length of each word in the dictionary for the hashing it takes O(k) time - O(m*k) - there would also be some complexity related to copying each substring and checking loop as well but that would be smaller than this so neglecting that (keeping simple)
class Solution {
private:
    unordered_set<string> present;

    int dfs(int i, string& s) {
        if (i == s.size()) {
            return 0;
        }

        int result = 1 + dfs(i + 1, s); // skipping this character
        for (int j = i; j < s.size(); j++) { // answer to all words including this character
            string current = s.substr(i, j - i + 1);
            if (present.find(current) != present.end()) {
                result = min(result, dfs(j + 1, s));
            }
        }

        return result;
    }
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        for (string word : dictionary) {
            present.insert(word);
        }

        return dfs(0, s);
    }
};

// optimization using dp (memoization - top down) : in the above approach we're traversing same suffix repeatedly and recalculating that - dp[length] = answer to length of substring 'length' - hence each substring traversed only once - exponential reduced to O(n) linear!
// Hence total n characters (lengths :- i values) -> n substrings -> using s.substr() => O(n^3)
// O(n^3 + m*k)
class Solution2 {
private:
    unordered_set<string> present;
    vector<int> dp;

    int dfs(int i, string& s, vector<int>& dp) {
        if (dp[i] != -1) {
            return dp[i];
        }

        int result = 1 + dfs(i + 1, s, dp);
        for (int j = i; j < s.size(); j++) {
            string current = s.substr(i, j - i + 1);
            if (present.find(current) != present.end()) {
                result = min(result, dfs(j + 1, s, dp));
            }
        }
        
        return dp[i] = result;
    }
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        for (string word : dictionary) {
            present.insert(word);
        }
        dp.resize(s.size() + 1, -1);
        dp[s.size()] = 0; // base case -> empty string means no remaining character

        return dfs(0, s, dp);
    }
};

// exactly similar can be done for prefix using bottom up dp - same complexity
class Solution3 {
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        unordered_set<string> words(dictionary.begin(), dictionary.end());
        int n = s.size();
        vector<int> dp(n+1, 0);

        for (int i = n - 1; i >= 0; i--) {
            dp[i] = 1 + dp[i+1]; // skipping this character
            for (int j = i; j < n; j++) {
                string current = s.substr(i, j - i + 1);
                if (words.find(current) != words.end()) {
                    dp[i] = min(dp[i], dp[j+1]); // taking ith character -> answer would be of remaining part
                }
            }
        }

        return dp[0];
    }
};

// top down dp: instead of checking each character using map -> try each word in the dictionary checking if that exists - find dp[length] = best possible answer using that word
// O(n*m*k)
class Solution4 {
private:
    vector<int> dp;
    unordered_set<string> words;

    int dfs(int i, string& s) {
        if (dp[i] != -1) {
            return dp[i];
        }

        int result = 1 + dfs(i + 1, s);
        for (string word : words) {
            if (i + word.size() > s.size()) continue;

            bool flag = true;
            for (int j = 0; j < word.size(); j++) {
                if (s[i+j] != word[j]) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                result = min(result, dfs(i + word.size(), s));
            }
        }

        return dp[i] = result;
    }
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        for (string word : dictionary) {
            words.insert(word);
        }
        dp.resize(s.size() + 1, -1);
        dp[s.size()] = 0;

        return dfs(0, s);
    }
};

// now just combination -> prefix optimization using prefix and using top down dp -> suffix optimization - O(n^2 + m*k) - (similar to word break ii - check /recursion)
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool endOfWord = false;
};

class Trie {
    public:
        TrieNode* root;

        Trie () {
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

class Solution5 {
private:
    vector<int> dp;

    int dfs(int i, const string& s, Trie& trie) {
        if (dp[i] != -1) {
            return dp[i];
        }

        int result = 1 + dfs(i + 1, s, trie); // skipping the current character
        TrieNode* current = trie.root;

        for (int j = i; j < s.size(); j++) {
            char c = s[j];
            if (current->children.find(c) == current->children.end()) break; // no word - skip rest of unnecessary prefixes
            current = current->children[c]; // move to the next character of the word 
            if (current->endOfWord) {
                result = min(result, dfs(j + 1, s, trie)); 
            } 
        }

        return dp[i] = result;
    }
public:
    int minExtraChar(string s, vector<string>& dictionary) {
        Trie trie;
        for (string word : dictionary) {
            trie.addWord(word);
        }

        dp.resize(s.size() + 1, -1);
        dp[s.size()] = 0;

        return dfs(0, s, trie);
    }
};
