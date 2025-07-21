/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool solve(const string& s, const string& t) {
    unordered_map<char, int> mp;
    int n = s.size(), m = t.size();
    bool flag = true;

    if ((n != m) || n <= 0 || m <= 0) return false;
    for (int i = 0; i < n; i++) {
        mp[s[i]]++; mp[t[i]]--;    
    }
    for (auto& [key, val] : mp) {
        if (val != 0) flag = false;
    }

    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s, t; cin >> s >> t;
        puts(solve(s, t) ? "Yes" : "No");
    }

    return 0;
}
