/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        int ans(0);
        unordered_map<char, int> mp;
        for (auto& c : s) {
            if (mp[c]) ans++;
            else {
                ans += 2;
                mp[c]++;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
