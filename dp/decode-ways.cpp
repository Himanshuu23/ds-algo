#include <bits/stdc++.h>
using namespace std;

// O(2^n), O(n): recursion, backtracking
class Solution {
private:
    unordered_map<int, char> mp;
    int count = 0;

    void backtrack(int i, const string& s) {
        if (i == (int)s.size()) {
            ++count;
            return;
        }
        if (s[i] == '0') return; // leading zeroes can never start anything from them - no char has value 0
        // take one digit
        int oneDigit = s[i] - '0';
        if (mp.count(oneDigit)) {
            backtrack(i + 1, s);
        }

        // take two digits
        if (i + 1 < s.size()) {
            int twoDigit = (s[i] - '0') * 10 + (s[i+1] - '0');
            if (mp.count(twoDigit)) {
                backtrack(i + 2, s);
            }
        }
    }
public:
    int numDecodings(string s) {
        int i = 1;
        for (char c = 'A'; c <= 'Z'; c++) {
            mp[i++] = c;
        }
        count = 0;
        backtrack(0, s);
        return count;
    }
};

// optimization using top down dp: O(n), O(n)
// dp[i] = number of ways to decode from 'i'
class Solution2 {
private:
    unordered_map<int, char> mp;
    vector<int> dp;

    int backtrack(int i, const string& s) {
        if (i == (int)s.size()) {
            return 1;
        }
        if (s[i] == '0') return 0; // leading zeroes can never start anything from them - no char has value 0
        if (dp[i] != -1) return dp[i];
        // take one digit
        int ways = 0;
        int oneDigit = s[i] - '0';
        if (mp.count(oneDigit)) {
            ways += backtrack(i + 1, s);
        }

        // take two digits
        if (i + 1 < s.size()) {
            int twoDigit = (s[i] - '0') * 10 + (s[i+1] - '0');
            if (mp.count(twoDigit)) {
                ways += backtrack(i + 2, s);
            }
        }

        return dp[i] = ways;
    }
public:
    int numDecodings(string s) {
        int i = 1;
        for (char c = 'A'; c <= 'Z'; c++) {
            mp[i++] = c;
        }
        dp.assign(s.size(), -1);
        return backtrack(0, s);
    }
};

// bottom down dp: O(n), O(n)
// dp[i] = number of ways to decode s[i:]
// base case dp[n] = 1 -> empty string has only one valid decoding
class Solution3 {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n + 1);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '0') {
                dp[i] = 0;
            } else {
                dp[i] = dp[i+1]; // taking one digit
                if (i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] < '7'))) {
                    dp[i] += dp[i+2]; // taking two digits only if they're in the limit 10-26
                }
            }
        }
        return dp[0];
    }
};

// space optimized bottom up dp: O(n), O(1)
// since current answer depends only only on two variables i + 1, i + 2
// dp1 = 1 (dp[n]), dp2 = 0 -> base case, dp -> current answer
class Solution4 {
public:
    int numDecodings(string s) {
        int dp = 0, dp2 = 0;
        int dp1 = 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '0') {
                dp = 0;
            } else {
                dp = dp1;
                if (i + 1 < s.size() && (s[i] == '1' || (s[i] == '2' && s[i + 1] < '7'))) {
                    dp += dp2;
                }
            }
            dp2 = dp1;
            dp1 = dp;
            dp = 0;
        }
        return dp1;
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
