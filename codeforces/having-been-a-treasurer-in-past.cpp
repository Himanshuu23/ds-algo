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
        if (n < 3) { cout << 0 << endl; continue; }
        ll c(0);
        for (char ch : s) if (ch == '-') ++c;
        ll dash = n-c;
        ll ans = dash*(c/2)*(c-c/2);
        cout << ans << endl;
    }

    return 0;
}
