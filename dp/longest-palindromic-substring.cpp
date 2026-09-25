#include <bits/stdc++.h>
using namespace std;

// try every possible substring and find the longest substring that is a palindrome: O(n^3), O(n)
class Solution {
public:
    string longestPalindrome(string s) {
        string answer = "";
        int length = 0;

        for (int i = 0; i < s.size(); i++) {
            for (int j = i; j < s.size(); j++) {
                int l = i, r = j;
                while (l < r && s[l] == s[j]) {
                    l++; r--;
                }
                if (l >= r && length < (j - i + 1)) {
                    answer = s.substr(i, j - i + 1);
                    length = j - i + 1;
                }
            }
        }

        return answer;
    }
};

// using dp: instead of rechecking we remember that string [i...j] is a palindrome -> dp[i][j] = true
// small edge case: when length of string is 1,2,3 j - i <= 2 then checking ends is enough for palindrome
// O(n^2), O(n^2)
class Solution2 {
public:
    string longestPalindrome(string s) {
        int answerIndex = 0, length = 0;
        int n = s.size();

        vector<vector<bool>> dp(n, vector<bool> (n, false));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i <= 2 || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    if (length < (j - i + 1)) {
                        answerIndex = i;
                        length = j - i + 1;
                    }
                }
            }
        }

        return s.substr(answerIndex, length);
    }
};

// two pointers: expand around centre - just have to do for both odd and even length strings
// O(n^2), O(1) extra space, O(n) space for output string
class Solution3 {
public:
    string longestPalindrome(string s) {
        int answerIndex = 0, length = 0;
        for (int i = 0; i < s.size(); i++) {
            // odd length
            int l = i, r = i;
            while (l >= 0 && r < s.size() && s[l] == s[r]) {
                if (r - l + 1 > length) {
                    answerIndex = l;
                    length = r - l + 1;
                }
                l--;
                r++;
            }
            // even length
            l = i, r = i + 1;
            while (l >= 0 && r < s.size() && s[l] == s[r]) {
                if (r - l + 1 > length) {
                    answerIndex = l;
                    length = r - l + 1;
                }
                l--;
                r++;
            }
        }

        return s.substr(answerIndex, length);
    }
};

// Manacher's Algorithm: O(n), O(n)
// (i) unify odd and even length palindromes by inserting a special character like '#' between characters "abba" -> "#a#b#b#a#" - now odd length (ii) use previous palindromic information to avoid re-checking characters (iii) maintain a current rightmost palindrome and mirror indices to reuse results.
// instead of expanding from center independently, this algorithm reuses symmetry, making it much faster than the two-pointer approach
// criteria for taking next centre:-
// (1) Totally contained under current palindrome - don't take that 
// (2) Current palindrome expands till end on input - don't take that
// (3) Palindrome expands atleast till right edge and its mirror palindrome is proper prefix - take this
// (4) Palindrome expands till right edge and its mirror expands beyond left edge - don't take that
// algorithm for coding: transform the string - insert # between characters and at both ends to handle odd/even palindromes uniformly. Create an array p[] where p[i] = radius of palindrome centered at index i in the transformed string. Maintain two pointers: center - center of the current rightmost palindrome and right - right boundary of that palindrome. 
// For each index i - if i is inside the current palindrome: initialize p[i] using its mirror around center. Expand around i while characters match. If the palindrome expands beyond right, update center and right.
// after processing - find the index with the maximum value in p convert that position back to the original string indices. - return the longest palindromic substring.
class Solution4 {
private:
    vector<int> manacher(string& s) {
        string t = "#" + string(1, s[0]);
        for (int i = 1; i < s.size(); i++) {
            t += "#" + string(1, s[i]);
        }
        t += "#";
        int n = t.size();
        vector<int> p(n, 0);
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) {
            p[i] = (i < r) ? min(r - i, p[l + (r - i)]) : 0; // i < r means if i is already inside the current window, we already know about it, its mirror position l + (r - i) would have roughly the same radius (if it falls inside the window), if current centre's radius goes out of range - next possible candidate for being the center (out of all candidates we take the one with maximum radius)
            while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) {
                p[i]++;
            }
            if (i + p[i] > r) { // if this palindrome extends pasts r, then update l, r to this new window
                l = i - p[i], r = i + p[i];
            }
        }
        return p;
    }
public:
    string longestPalindrome(string s) {
        vector<int> p = manacher(s);
        int answerLength = 0, centerIndex = 0;
        for (int i = 0; i < p.size(); i++) {
            if (p[i] > answerLength) {
                answerLength = p[i];
                centerIndex = i;
            }
        }
        int answerIndex = (centerIndex - answerLength) / 2;
        return s.substr(answerIndex, answerLength);
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
