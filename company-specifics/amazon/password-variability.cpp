#include <bits/stdc++.h>
using namespace std;

/*
Given a string password consisting of lowercase English letters, its variability is defined as the number of distinct password strings that can be obtained by reversing any one contiguous substring of the original password.Task:Return a long integer representing the total number of distinct strings that can be formed.Constraints:$1 \le \text{length of password} \le 10^5$All characters in password are lowercase English letters (a-z).Sample CasesExample 1:Input: password = "abc"Output: 4Explanation:Reverse length 1 substrings $\rightarrow$ "abc"Reverse "ab" $\rightarrow$ "bac"Reverse "bc" $\rightarrow$ "acb"Reverse "abc" $\rightarrow$ "cba"Distinct strings: {"abc", "bac", "acb", "cba"} ($4$ distinct strings).Sample Case 0:Input: password = "abaa"Output: 4Explanation:The distinct strings formed are "abaa", "aaba", "baaa", and "aaab"
Link - https://leetcode.com/discuss/post/4749861/amazon-oa-by-anonymous_user-1yoe/
*/

// reversing substring(i, j) when s[i] == s[j] does nothing just gives the same string while reversing when s[i] != s[j] produces distinct substring. Total pairs (i, j) where i < j are (n*(n-1))/2 where n is the length of the password. total pairs with s[i] == s[j] would be count each char then for each of those char -> (count[char]*(count[char]-1))/2. Hence different would be total - same pairs and + 1 for the original string as well
// O(n), O(1)
long long solve(const string& password) {
    long long n = password.size();
    long long total_pairs = (n*(n-1))/2;
    vector<long long> frequency(26, 0);
    for (char c : password) {
        frequency[c-'a']++;
    }

    long long same_pairs = 0;
    for (int i = 0; i < 26; i++) {
        same_pairs += (frequency[i]*(frequency[i]-1))/2;
    }

    long long different_pairs = total_pairs - same_pairs;
    return 1 + different_pairs;
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
