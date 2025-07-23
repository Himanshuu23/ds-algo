/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(const string& s, int k) {
    int st(0), e(0), ans(0), mx(0);
    unordered_map<char, int> mp;

    while (e < s.size()) {
        mp[s[e]]++;
        mx = max(mx, mp[s[e]]);

        if ((e - st + 1) - mx > k) {
            mp[s[e]]--;
            st++;
        }
        ans = max(ans, e - st + 1);
        e++;
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int k; cin >> k;
        string s; cin >> s;
        cout << solve(s, k) << endl;
    }

    return 0;
}
