/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;

// backtracking : if [start...end] is palindrome take it in current path and start next part (partition from end + 1)
// try all possible splits/partitions
// O(n*2^n) -> try n possible partitions and for each option take element in current partition, don't take it 
// O(n) extra space, O(n*2^n) for output
bool isPalin(const string& s, int l, int r) {
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

void dfs(int start, const string& s, vector<string>& path, vector<vector<string>>& res) {
    if (start == s.size()) {
        res.push_back(path);
        return;
    }
    for (int end = start; end < s.size(); ++end) {
        if (isPalin(s, start, end)) {
            path.push_back(s.substr(start, end - start + 1));
            dfs(end + 1, s, path, res);
            path.pop_back();
        }
    }
}

// optimization: we're rechecking multiple intervals repeatedly for palindrome - use dp for that -> precompute so when we backtrack we can directly check whether dp[i][j] is palindrome [i...j]
// conditions for checking these, firstly i is start and i + l - 1 is end 
// Now if (s[start] == s[end]) then dp[start][end] is true or if (i + 1 > i + l - 2) -> this is condition for two substring of length one or two where we don't have to check inside or dp[start + 1][end-1] is true then these are also true
// checking each length 1, length 2, length 3... so on so hence for checking a b a with start = 0 and end = 2 we already know its palindrome coz 'b' is palindrome inside
// same complexities as above just O(n^2) extra space
class Solution {
private:
    vector<vector<bool>> dp;

    void dfs(int start, const string s, vector<string>& path, vector<vector<string>>& result) {
        if (start == s.size()) {
            result.push_back(path);
            return;
        }

        for (int end = start; end < s.size(); end++) {
            if (dp[start][end]) {
                path.push_back(s.substr(start, end - start + 1));
                dfs(end + 1, s, path, result);
                path.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        dp.resize(n, vector<bool> (n));
        for (int l = 1; l <= n; l++) {
            for (int i = 0; i <= n - l; i++) {
                dp[i][i+l-1] = s[i] == s[i+l-1] &&
               (i + 1 > i+l-2 || dp[i+1][i+l-2]);
            }
        }

        vector<vector<string>> result;
        vector<string> path;
        dfs(0, s, path, result);
        
        return result;
    }
};

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        vector<vector<string>> res;
        vector<string> path;
        dfs(0, s, path, res);
        for (auto& part : res) {
            for (auto& p : part) cout << p << " ";
            cout << endl;
        }
    }
    return 0;
}
