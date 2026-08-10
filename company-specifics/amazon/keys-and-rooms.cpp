#include <bits/stdc++.h>
using namespace std;

/*
There are $n$ rooms labeled 0 to n - 1. All rooms are locked except room 0, which is initially unlocked. Your goal is to visit all the rooms.When you enter a room, you may find a set of keys inside it. Each key has a number on it denoting which room it unlocks, and you can take all of them with you to open other locked rooms.Task:Return true if you can visit all $n$ rooms, or false otherwise.Sample CasesExample 1:Input: rooms = [[1], [2], [3], []]Output: trueExplanation:Start in room 0 $\rightarrow$ collect key 1.Open room 1 $\rightarrow$ collect key 2.Open room 2 $\rightarrow$ collect key 3.Open room 3.All rooms visited $\rightarrow$ true.Example 2:Input: rooms = [[1, 3], [3, 0, 1], [2], [0]]Output: falseExplanation: You can never enter room 2.
Link - https://leetcode.com/discuss/post/6414650/amazon-sde-1-interview-experience-februa-k70a/
*/

// O(V + E), O(V), V - number of rooms and E - total keys
bool canVisitAllRooms(int n, vector<vector<int>>& rooms) {
    vector<bool> visited(n, false);
    queue<int> q;

    visited[0] = true;
    q.push(0);
    int count = 1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        for (int key : rooms[current]) {
            if (!visited[key]) {
                q.push(key);
                visited[key] = true;
                count++;
            }
        }
    }

    return count == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        vector<vector<int>> rooms = { {1, 3}, {3, 0, 1}, {2}, {0} };
        cout << canVisitAllRooms(rooms.size(), rooms) << '\n';
    }

    return 0;
}
