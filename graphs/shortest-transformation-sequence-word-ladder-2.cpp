/*
    author: Himanshuu23
*/

#include <bits/stdc++.h>
using namespace std;

// O(N2*L)
bool unitDifference(string& first, string& second) {
	int count = 0;
	if (first.size() != second.size()) return false;
	for (int i = 0; i < first.size(); i++) {
		if (first[i] != second[i]) count++;
	}

	return count == 1;
}

void buildGraph(vector<string>& wordList, vector<vector<int>>& graph) {
	int n = wordList.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (unitDifference(wordList[i], wordList[j])) graph[i].push_back(j);
		}
	}
}

vector<int> bfs2(int n, int begin, int end, vector<vector<int>>& graph) {
	vector<int> distance(n, INT_MAX);
	queue<int> q;
	q.push(begin);
	distance[begin] = 0;
	while (!q.empty()) {
		int node = q.front(); q.pop();
		if (node == end) break;
		for (int neighbour : graph[node]) {
			if (distance[neighbour] == INT_MAX) {
				distance[neighbour] = distance[node] + 1;
				q.push(neighbour);
			}
		}
	}

	return distance;
}

void dfs2(int node, vector<vector<int>>& graph, vector<int>& distance, vector<vector<string>>& answer, vector<string>& current, int end, vector<string>& wordList) {
	current.push_back(wordList[node]);
	if (node == end) {
		answer.push_back(current);
	} else {
		for (int neighbour : graph[node]) {
			if (distance[neighbour] == distance[node] + 1)
				dfs2(neighbour, graph, distance, answer, current, end, wordList);
		}
	}
	current.pop_back();
}

// better solution - O(N*L*26)
void dfs(string word, string beginWord, unordered_map<string, vector<string>>& parentMap,
         vector<string>& path, vector<vector<string>>& result) {
    if (word == beginWord) {
        path.push_back(word);
        reverse(path.begin(), path.end());
        result.push_back(path);
        reverse(path.begin(), path.end());
        path.pop_back();
        return;
    }

    path.push_back(word);
    for (string& parent : parentMap[word]) {
        dfs(parent, beginWord, parentMap, path, result);
    }
    path.pop_back();
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    vector<vector<string>> result;

    if (!wordSet.count(endWord)) return result;

    unordered_map<string, vector<string>> parentMap;
    unordered_set<string> visited;
    unordered_set<string> currentLevelVisited;

    queue<string> q;
    q.push(beginWord);
    visited.insert(beginWord);
    bool found = false;

    while (!q.empty() && !found) {
        int size = q.size();
        currentLevelVisited.clear();

        for (int i = 0; i < size; i++) {
            string word = q.front(); q.pop();

            string original = word;
            for (int j = 0; j < word.size(); j++) {
                char old = word[j];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[j] = ch;
                    if (!wordSet.count(word) || visited.count(word)) continue;

                    parentMap[word].push_back(original);

                    if (word == endWord) found = true;

                    if (!currentLevelVisited.count(word)) {
                        q.push(word);
                        currentLevelVisited.insert(word);
                    }
                }
                word[j] = old;
            }
        }

        for (auto& w : currentLevelVisited) visited.insert(w);
    }

    if (!found) return result;

    vector<string> path;
    dfs(endWord, beginWord, parentMap, path, result);
    return result;
}

int main() {
    int t; cin >> t;
    while(t--) {
        string beginWord = "hit", endWord = "cog";
        vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

        vector<vector<string>> sequences = findLadders(beginWord, endWord, wordList);

        cout << "All shortest transformation sequences:\n";
        for (auto& seq : sequences) {
            for (auto& word : seq) cout << word << " ";
            cout << endl;
        }
    }

    return 0;
}
