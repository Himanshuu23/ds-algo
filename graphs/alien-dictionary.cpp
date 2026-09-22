#include <bits/stdc++.h>
using namespace std;

// characters that are present early -> we can consider that as directed edge from c -> child and now we just have to do topological sort. 
// Two things though: (i) there shouldn't be any cycles return "" (ii) special case: word present then its prefix present which is invalid -> "abc", "ab"
// dfs is detecting cycle in directed graph through three states: if character is present in visited: unvisited, visited[char] = true: currently processing, visited[char] = false already processed
// O(N + V + E), O(V + E), V is number of unique characters, E is number of edges and N is the sum of lengths of all words
class Solution {
private:
    unordered_map<char, unordered_set<char>> adj;
    unordered_map<char, bool> visited;
    string result;

    bool dfs(char c) {
        if (visited.find(c) != visited.end()) {
            return visited[c];
        }

        visited[c] = true;
        for (char child : adj[c]) {
            if (dfs(child)) {
                return true;
            }
        }
        visited[c] = false;
        result.push_back(c);
        return false;
    }
public:
    string foreignDictionary(vector<string>& words) {
        for (const string& word : words) { // O(N)
            for (char c : word) {
                adj[c];
            }
        }

        for (int i = 0; i < words.size() - 1; i++) { // O(N)
            string word1 = words[i], word2 = words[i+1];
            int minLength = min(word1.size(), word2.size());
            if (word1.size() > word2.size() && word1.substr(0, minLength) == word2.substr(0, minLength)) {
                return "";
            }
            for (int j = 0; j < minLength; j++) {
                if (word1[j] != word2[j]) {
                    adj[word1[j]].insert(word2[j]);
                    break;
                }
            }
        }

        for (auto& [c, children] : adj) { // O(V + E)
            if (dfs(c)) {
                return "";
            }
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

// same complexity and approach just using kahn algorithm (topological sort)
class Solution2 {
public:
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> indegree;

        for (const string& word : words) {
            for (char c : word) {
                adj[c];
                indegree[c] = 0;
            }
        }

        for (int i = 0; i < words.size() - 1; i++) {
            string word1 = words[i], word2 = words[i+1];
            int minLength = min(word1.size(), word2.size());
            if (word1.size() > word2.size() && word1.substr(0, minLength) == word2.substr(0, minLength)) {
                return "";
            }
            for (int j = 0; j < minLength; j++) {
                if (word1[j] != word2[j]) {
                    if (!adj[word1[j]].count(word2[j])) {
                        adj[word1[j]].insert(word2[j]);
                        indegree[word2[j]]++;
                    }
                    break;
                }
            }
        }

        queue<char> q;
        for (auto& [c, degree] : indegree) {
            if (degree == 0) {
                q.push(c);
            }
        }

        string result;
        while (!q.empty()) {
            char ch = q.front();
            q.pop();
            
            result += ch;
            for (char neighbor : adj[ch]) {
                if (--indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return result.size() == indegree.size() ? result : "";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
