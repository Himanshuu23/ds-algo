/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(const string& s) {
    int ans(0), start(0), end(0);
    unordered_map<char, int> mp;

    while (end < s.size()) {
        if (mp.count(s[end]) && mp[s[end]] >= start) {
            start = mp[s[end]] + 1;
        }
        mp[s[end]] = end;

        ans = max(ans, end - start + 1);
        end++;
    }

    return ans;
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
