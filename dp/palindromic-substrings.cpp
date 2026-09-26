#include <bits/stdc++.h>
using namespace std;

// brute force: O(n^3), O(1)
class Solution {
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }
public:
    int countSubstrings(string s) {
        int n = s.size();
        int answer = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalindrome(s, i, j)) ++answer;
            }
        }
        return answer;
    }
};

// using dp: O(n^2), O(n^2)
class Solution2 {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool> (n, false));

        int answer = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && ((j - i <= 2) || dp[i+1][j-1])) {
                    dp[i][j] = true;
                    ++answer;
                }
            }
        }
        return answer;
    }
};

// using two pointers: O(n^2), O(1)
class Solution3 {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int answer = 0;
        for (int i = 0; i < n; i++) {
            int l = i, r = i;
            while (l >= 0 && r < n && s[l--] == s[r++]) {
                ++answer;
            }
            l = i, r = i + 1;
            while (l >= 0 && r < n && s[l--] == s[r++]) {
                ++answer;
            }
        }
        return answer;
    }
};

// O(n), O(n) - manacher's algorithm
class Solution4 {
private:
    vector<int> manacher(string& s) {
        if (!s.size()) return {};
        string t = "#" + string(1, s[0]);
        for (int i = 1; i < s.size(); i++) {
            t += "#" + string(1, s[i]);
        }
        t += "#";
        int n = t.size();
        vector<int> p(n, 0);
        int l = 0, r = 0;
        for (int i = 0; i < n; i++) { // taking every 'i' as center
            p[i] = (i < r) ? min(r - i, p[l + (r - i)]) : 0; // if inside the current window - less than rightmost index of window then take that as current centre else start again from 0
            while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 && t[i + p[i] + 1] == t[i - p[i] - 1]) { // expanding the current window
                p[i]++;
            }
            if (i + p[i] > r) { // updating r and l if the current window is greater
                l = i - p[i], r = i + p[i];
            }
        }
        return p;
    }
public:
    int countSubstrings(string s) {
        vector<int> p = manacher(s);
        int answer = 0;
        for (int i : p) {
            answer += (i + 1) / 2;
        }
        return answer;
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
