#include<bits/stdc++.h>
using namespace std;

// O(v + e), O(v), v -> vertices and e -> edges
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> indegree(n + 1, 0), outdegree(n + 1, 0);

        for (int i = 0; i < trust.size(); i++) {
            indegree[trust[i][1]]++;
            outdegree[trust[i][0]]++;
        }

        int answer = -1;

        for (int i = 1; i <= n; i++) {
            if (indegree[i] == n - 1 && outdegree[i] == 0) {
                answer = i;
                break;
            }
        }

        return answer;
    }
};

// combining both into single array
class Solution2 {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        vector<int> delta(n + 1, 0);

        for (int i = 0; i < trust.size(); i++) {
            delta[trust[i][1]]++;
            delta[trust[i][0]]--;
        }

        for (int i = 1; i <= n; i++) {
            if (delta[i] == n - 1) {
                return i;
            }
        }

        return -1;
    }
};
