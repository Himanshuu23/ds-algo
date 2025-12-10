/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string reverseString(string s) {
    string ans;
    for (int i = s.size() - 1; i >= 0; i--) ans += s[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s1, s2; cin >> s1;
        int n = s1.size();
        vector<vector<int>> dp(n+1, vector<int> (n+1, 0));

        s2 = reverseString(s1);
        for (int i = n-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (s1[i] == s2[j]) dp[i][j] = 1 + dp[i+1][j+1];
                else dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }

        cout << dp[0][0] << endl;
    }

    return 0;
}
