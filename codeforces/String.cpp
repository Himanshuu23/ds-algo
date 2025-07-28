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
        string s; cin >> s;
        int ans(0);
        for (char c : s) if (c == '1') ans++;
        cout << ans << endl;
    }

    return 0;
}
