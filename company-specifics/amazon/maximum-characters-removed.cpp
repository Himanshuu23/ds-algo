#include <bits/stdc++.h>
using namespace std;

/*
Problem StatementYou are given a string s representing a machine. The type of a string is defined as a pair consisting of its first character and its last character: (s[0], s[n-1]).In a single process, you can remove any number of characters from the start and/or the end of the string. The resulting substring must have the exact same type as the original string.Find the maximum number of characters you can remove while preserving the string's original type.Constraints$1 \le \vert{}s\vert{} \le 10^5$s consists of lowercase English letters.Sample CasesSample 1Input: s = "abade"Original Type: ('a', 'e')Optimal Substring: "ade" (indices 2 to 4) starts with 'a' and ends with 'e'.Removed: "ab" (length 2).Output: 2Sample 2Input: s = "abacaba"Original Type: ('a', 'a')Optimal Substring: "a" (any single 'a', e.g., index 0, length 1).Removed: "bacaba" (length 6).Output: 6
link : https://leetcode.com/discuss/post/7112319/amazon-oa-sde-august-2025-by-anonymous_u-o8ee/
*/

// O(N), O(1) - just finding closest positions of x, y
int solve(string& s) {
    char x = s[0], y = s.back();
    int n = s.size();
    if (x == y) return n - 1;
    int answer = INT_MAX;
    int last_x = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == x) {
            last_x = i;
        }
        if (s[i] == y && last_x != -1) {
            answer = min(answer, i - last_x + 1);
        }
    }

    return n - answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s; cin >> s;
        cout << solve(s) << '\n';
    }

    return 0;
}
