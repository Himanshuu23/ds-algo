#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    pair<int, int> numberOfZeroesOnes(const string& s) {
    pair<int, int> p;
    for (auto& c : s) (c == '0') ? p.first++ : p.second++;
    return p;
}

int solve(vector<string>&s, int m, int n, int i, vector<vector<vector<int>>>& dp) {
    if (i == s.size()) return 0;
    if (dp[i][m][n] != -1) return dp[i][m][n];

    int exclude = solve(s, m, n, i+1, dp);
    int include = 0;
    pair<int, int> p = numberOfZeroesOnes(s[i]);
    if (p.first <= m && p.second <= n) include = 1 + solve(s, m-p.first, n-p.second, i+1, dp);
    return dp[i][m][n] = max(include, exclude);
}

    int findMaxForm(vector<string>& strs, int m, int n) {
        vector dp(strs.size()+1, vector(m+1, vector<int>(n+1, -1)));
        return solve(strs, m, n, 0, dp);
    }
};
