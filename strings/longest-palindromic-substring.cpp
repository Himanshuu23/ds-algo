/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void usingDP() {
    string a, b; cin >> a;
    int n = a.size();
    b = a;
    reverse(b.begin(), b.end());
    vector<vector<int>> dp(n+1, vector<int> (n+1, 0));

    string answer;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i-1] == b[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
            int revStart = n - j;
            if (dp[i][j] > answer.size() && revStart == i - dp[i][j]) answer = a.substr(i-dp[i][j], dp[i][j]);
        }
    }

    cout << answer << '\n';
}

string solve(string s) {
    if (s.empty()) return "";

    int start(0), maxLen(1);
    for (int center = 0; center < s.size(); center++) {
        int left = center, right = center;
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                start = left;
                maxLen = right - left + 1;
            }
            left--; right++;
        }

        left = center; right = center + 1;
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                start = left;
                maxLen = right - left + 1;
            }
            left--; right++;
        }
    }

    return s.substr(start, maxLen);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s; cin >> s;
        cout << solve(s) << endl;
    }

    return 0;
}
