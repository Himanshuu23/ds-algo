
/*
    author: Himanshuu23
*/

#include <bits/stdc++.h>
using namespace std;

// Using bfs : just each word that has difference of one character can be the next node of the graph -> making undirected graph of the given words and starting from beginWord and finding shortest distance to endWord and bfs provides shortest path by default in such case.
// using hash maps for O(1) lookup of words

// depending on the usecase we can use any approach - word length is more or there are more number of words

// O(n^2 * m)
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (find(wordList.begin(), wordList.end(), endWord) == wordList.end() || beginWord == endWord) return 0;
        int n = wordList.size(), m = wordList[0].size();
        vector<vector<int>> adj(n);
        unordered_map<string, int> mp;
        for (int i = 0; i < n; i++) {
            mp[wordList[i]] = i; 
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int count = 0; // total differing characters between the two strings we're comparing
                for (int k = 0; k < m; k++) {
                    if (wordList[i][k] != wordList[j][k]) ++count;
                }
                if (count == 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        queue<int> q;
        int result = 1;
        unordered_set<int> visited;

        string word = beginWord;
        for (int i = 0; i < m; i++) {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == original) continue;
                word[i] = ch;
                if (mp.find(word) != mp.end() && visited.find(mp[word]) == visited.end()) {
                    q.push(mp[word]);
                    visited.insert(mp[word]);
                }
            }
            word[i] = original;
        }

        while (!q.empty()) {
            result++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int node = q.front();
                q.pop();
                if (wordList[node] == endWord) {
                    return result;
                }
                for (int neighbor : adj[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }

        return 0;
    }
};

// same approach only just without graphs
// O(m^2 * n), O(m^2 * n) - where n are the number of words and n is the size of the word
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord)) return 0; // End word must be in the list

    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    unordered_set<string> visited;
    visited.insert(beginWord);

    while (!q.empty()) {
        auto [word, level] = q.front(); q.pop();

        for (int i = 0; i < word.length(); i++) {
            string temp = word;
            for (char ch = 'a'; ch <= 'z'; ch++) {
                temp[i] = ch;
                if (temp == endWord) return level + 1;
                if (wordSet.count(temp) && !visited.count(temp)) {
                    visited.insert(temp);
                    q.push({temp, level + 1});
                }
            }
        }
    }

    return 0; // No transformation found
}

int main() {
    int t; cin >> t;
    while(t--) {
        string beginWord = "hit", endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
        int result = ladderLength(beginWord, endWord, wordList);
        cout << "Shortest transformation length: " << result << "\n";
    }
    return 0;
}

