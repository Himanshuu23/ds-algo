#include <bits/stdc++.h>
using namespace std;

/*
 Given two strings pat (the wildcard pattern) and txt (the target text), check if pat matches txt completely.  The wildcard pattern pat can include the special characters:? – matches any single character.  * – matches any sequence of characters (including an empty sequence).  The match must cover the entire string txt (not a partial match).  Input Formatpat: A string representing the wildcard pattern.  txt: A string representing the text.Output FormatReturn true (or 1) if pat matches txt, else return false (or 0).  Constraints$1 \le \vert{}\text{pat}\vert{}, \vert{}\text{txt}\vert{} \le 1000$Expected Time Complexity: $\mathcal{O}(\vert{}\text{pat}\vert{} \times \vert{}\text{txt}\vert{})$Expected Auxiliary Space: $\mathcal{O}(\vert{}\text{pat}\vert{} \times \vert{}\text{txt}\vert{})$ExamplesExample 1Input: pat = "ba*a?", txt = "baaabab"Output: true (or 1)  Explanation: Replace * with "aab" and ? with 'b'.Example 2Input: pat = "a*ab", txt = "baaabab"Output: false (or 0)Explanation: pat starts with 'a', but txt starts with 'b', so they cannot match.
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// using dynamic programming
// T[i][j] = boolean 2d array tells whether substring 0 to i in string and 0 to j in pattern are match or not
// it can take two values : (1) T[i][j] = T[i-1][j-1] if string[i] == pattern[j] (if i and j are same then excluding i and j whether the rest of the string are match or not so we check T[i-1][j-1]) OR pattern[j] == '?' (2) T[i][j] = T[i-1][j] || T[i][j-1] if pattern[j] == '*' so T[i][j-1] means in string 0 till i matched and in pattern 0 to j-1 matched and hence '*' representing zero sequence of characters - means if string is xay and pattern is x?y* then x?y already matches we can take * as zero sequence to match the pattern. T[i][j-1] means in xay and x?y* we take last character of string as well to match so we match xa and x?y which is false - any of this true then T[i][j] is true
// if none of these match then T[i][j] = false
// Base Cases :- 
// T[0][0] = true means if pattern is empty then empty string matches that pattern 
// if row (or X axis) of grid => pattern and if col (or Y axis) -> string
// but T[0][1...N] = False since pattern is empty then it cannot match with string 
// similarly T[1...M][0] = False
// considering length of string is M and of pattern is N
// O(N*M), O(N*M) where N -> length of the string, M -> length of the pattern
bool isMatch(string& s, string& pattern) {
    // replacing multiple * with single *
    int writeIndex = 0;
    bool isFirst = true;
    for (int i = 0; i < pattern.size(); i++) {
        if (pattern[i] == '*') {
            if (isFirst) {
                pattern[writeIndex++] = pattern[i];
                isFirst = false;
            }
        } else {
            pattern[writeIndex++] = pattern[i];
            isFirst = true;
        }
    }

    vector<vector<bool>> dp(s.size() + 1, vector<bool> (writeIndex + 1, false));
    if (writeIndex > 0 && pattern[0] == '*') {
        dp[0][1] = true; // empty string matches single '*' pattern
    }

    dp[0][0] = true;
    for (int i = 1; i < dp.size(); i++) {
        for (int j = 1; j < dp[0].size(); j++) {
            if (pattern[j-1] == '?' || s[i-1] == pattern[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else if (pattern[j-1] == '*') {
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
        }
    }

    return dp[s.size()][writeIndex];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s, pattern; 
        cin >> s >> pattern;
        cout << isMatch(s, pattern) << '\n';
    }

    return 0;
}
