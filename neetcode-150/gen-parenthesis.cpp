/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
    vector<string> ans;
public:

    void solve(string curr, int open, int close, int n) {
        if (curr.size() == 2 * n) {
            ans.push_back(curr);
            return;
        }
        if (open < n) solve(curr+"(",open+1,close,n);
        if (close < open) solve(curr+")",open,close+1,n);
    }

    vector<string> generateParenthesis(int n) {
        solve("",0,0,n);
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
