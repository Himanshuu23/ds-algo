#include<bits/stdc++.h>
using namespace std;

// using bfs - each combination is like a node in a graph where we have to find from that combination shortest path to the target. Now we push all deadends into a visited map so we don't consider them ever. For each pattern formed till now we push into the queue all possible patterns by moving each of four locks up and down and push into the queue. When we have reached the target node we can safely return the steps since bfs gurantees it would be shortest path as we traverse all paths with step = 1 before step = 2.
// O(d^n + m), O(d^n) where d is the number of digit (0 - 9), n are number of wheels that is 4 and m are number of deadends
class Solution {
private:
    vector<string> children(string lock) {
        vector<string> result;
        for (int i = 0; i < 4; i++) {
            string next = lock;
            next[i] = (next[i] - '0' + 1) % 10 + '0';
            result.push_back(next);

            next = lock;
            next[i] = (next[i] - '0' - 1 + 10) % 10 + '0'; // (extra + 10 to avoid making it negative)
            result.push_back(next);
        }
        return result;
    }
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> visit(deadends.begin(), deadends.end());
        if (visit.count("0000")) return -1;

        queue<pair<string, int>> q;
        q.push({"0000", 0});
        visit.insert("0000");

        while (!q.empty()) {
            auto [lock, turns] = q.front();
            q.pop();

            if (lock == target) return turns;
            for (string child : children(lock)) {
                if (!visit.count(child)) {
                    q.push({child, turns + 1});
                    visit.insert(child);
                }
            }
        }

        return -1;
    }
};

// same bfs approach, same complexity - just instead of using helper function, for each lock going in two directions forward and backwards
class Solution2 {
public:
    int openLock(vector<string>& deadends, string target) {
        if (target == "0000") return 0;

        unordered_set<string> visited(deadends.begin(), deadends.end());
        if (visited.count("0000")) return -1;

        queue<string> q;
        q.push("0000");
        visited.insert("0000");
        int steps = 0;

        while (!q.empty()) {
            ++steps;
            int size = q.size(); // store it early since inside loop we're pushing inside the queue so q.size() would change
            for (int i = 0; i < size; i++) {
                string lock = q.front();
                q.pop();

                for (int j = 0; j < 4; j++) {
                    for (int move : {1, -1}) {
                        string nextLock = lock;
                        nextLock[j] = (nextLock[j] - '0' + move + 10) % 10 + '0';
                        if (visited.count(nextLock)) continue;
                        if (nextLock == target) return steps;
                        q.push(nextLock);
                        visited.insert(nextLock);
                    }
                }
            }
        }

        return -1;
    }
};

// optimization: we're currently exploring many waste states of the locks which are not required so to remove those - we expand the states from both the sides - source and target and when they meet we found the target! This is faster since we're not exploring waste states and always expanding the smaller set (source, target) which improves the overall searching. Time complexity is the same
class Solution3 {
public:
    int openLock(vector<string>& deadends, string target) {
        if (target == "0000") return 0;

        unordered_set<string> visited(deadends.begin(), deadends.end());
        if (visited.count("0000")) return -1;

        unordered_set<string> begin = {"0000"}, end = {target};
        int steps = 0;

        while (!begin.empty() && !end.empty()) {
            if (begin.size() > end.size()) swap(begin, end);
            steps++;
            unordered_set<string> temporary;

            for (const string& lock : begin) {
                for (int i = 0; i < 4; i++) {
                    for (int j : {1, -1}) {
                        string nextLock = lock;
                        nextLock[i] = (nextLock[i] - '0' + j + 10) % 10 + '0';

                        if (end.count(nextLock)) return steps;
                        if (visited.count(nextLock)) continue;

                        visited.insert(nextLock);
                        temporary.insert(nextLock);
                    }
                }
            }
            begin = temporary;
        }

        return -1;
    }
};
