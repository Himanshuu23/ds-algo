/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(const string& s) {
    int bal(0);
    for (int i = 1; i + 1 < s.size(); i++) {
        if (s[i] == '(') bal++;
        else bal--;
        if (bal < 0) {
            cout << "YES\n";
            return;
        }
    }

    if (!bal) cout << "NO" << endl;
    else cout << "YES" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s; cin >> s;
        solve(s);
    }

    return 0;
}
