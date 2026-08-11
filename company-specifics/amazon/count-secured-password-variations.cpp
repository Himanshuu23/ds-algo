#include <bits/stdc++.h>
using namespace std;

/*
In an Amazon security analysis task, two passwords have been generated:s: The customer's password.t: The system-generated password.A secured variation is defined as a non-empty subsequence of s that is lexicographically greater than t.TaskCount how many subsequences of s are lexicographically greater than t. Since the total count can be very large, return the result modulo $10^9 + 7$.DefinitionsSubsequence: A sequence derived from $s$ by deleting zero or more characters without changing the order of the remaining characters.Lexicographically Greater: A sequence $x$ is lexicographically greater than $y$ if:$x[i] > y[i]$ at the first index $i$ where $x$ and $y$ differ, OR$\vert{}x\vert{} > \vert{}y\vert{}$ and $y$ is a prefix of $x$.Constraints$1 \le \vert{}s\vert{} \le 10^5$$1 \le \vert{}t\vert{} \le 100$Both $s$ and $t$ consist of lowercase English letters ('a' – 'z').Sample CasesSample Case 0Input: s = "bab", t = "ab"Output: 5Explanation:
All possible subsequences of s = "bab" and their comparisons with t = "ab":"b" $\rightarrow$ Greater"ba" $\rightarrow$ Greater"bb" $\rightarrow$ Greater"bab" $\rightarrow$ Greater"a" $\rightarrow$ Smaller"ab" $\rightarrow$ Equal"b" $\rightarrow$ GreaterTotal lexicographically greater subsequences = 5.
Sample Case 1
Input: s = "aba", t = "ab"
Output: 3
Explanation:
The valid greater subsequences are "aba", "b", and "ba".
Link - https://leetcode.com/discuss/post/6331313/amazon-oa-2025-sde-by-anonymous_user-eplv/
*/

// first thing to notice is value of length of s and t combined are 10 power 7 means we can do double loop - solution is dp we have dp[i][j] where state represents dp[i][j] = total subsequences of s starting from index i lexicographically greater than subsequence of t starting from j and hence we start from last character and build to the top - using the fact that if some character is greater than t at the start then we don't need to check rest of the characters at the end
// O(|s||t|), O(|s||t|)
long long findLexicographicallyGreater(const string& s, const string& t) {
    int m = s.size(), n = t.size();
    long long MOD = 1e9 + 7;

    // pre computing powers of two
    vector<long long> powers_of_two(m+1, 1);
    for (int i = 1; i <= m; i++) {
        powers_of_two[i] = (powers_of_two[i-1] * 2) % MOD;
    }

    vector<vector<long long>> dp(m+1, vector<long long> (n+1, 0));

    // base case when j = n means we have no character of 't' to compare empty string - means all subsequences starting from i are answer except 1 that is empty so -1
    for (int i = 0; i <= m; i++) {
        dp[i][n] = (powers_of_two[m-i] - 1 + MOD) % MOD;
    }

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            // skip s[i]
            long long count = dp[i+1][j];

            // include s[i]
            if (s[i] > t[j]) {
                count = (count + powers_of_two[m - 1 - i]) % MOD;
            } else if (s[i] == t[j]) {
                count = (count + dp[i+1][j+1]) % MOD;
            }
            // nothing for s[i] < t[j]
            dp[i][j] = count;
            // directly adding in count where had answer for skipped s[i] since for a string starting at i subsequences are both -> exclude s[i] + include s[i] -> "abc" -> for s[0] 'a' total substrings -> without taking 'a' + take 'a'
        }
    }

    return (dp[0][0] + MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s, t; cin >> s >> t;
        cout << findLexicographicallyGreater(s, t) << '\n';
    }

    return 0;
}
