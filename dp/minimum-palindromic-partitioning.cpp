#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string &s, int i , int j, vector<vector<int>> &dp) {
    if (i >= j) return true;
    if (dp[i][j] != -1) return dp[i][j];
    return dp[i][j] = (s[i] == s[j] && isPalindrome(s, i+1, j-1, dp));
}

int main() {
    string s; cin >> s;
    int n = s.size();
    vector<vector<int>> dp(n, vector<int> (n, -1));
    vector<int> minCuts(n, INT_MAX);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (isPalindrome(s, j, i, dp)) {
                if (j == 0) minCuts[i] = 0;
                else minCuts[i] = min(minCuts[i], minCuts[j-1] + 1);
            }
        }
    }
    
    cout << minCuts[n-1] << endl;

    return 0;
}
