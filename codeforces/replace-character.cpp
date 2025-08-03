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
        int v[26] = {0};
        for (int i = 0; i < n; i++) v[s[i] - 'a']++;
        int mn(n+1), mx(0);
        char mnc(' '), mxc(' ');
        for (int i = 0; i < 26; i++) {
            if (!v[i]) continue;
            if (v[i] < mn) { mn = v[i]; mnc = 'a' + i; }
            if (v[i] >= mx) { mx = v[i]; mxc = 'a' + i; }
        }
        for (int i = 0; i < n; i++) { if(s[i] == mnc) { s[i] = mxc; break; }}
        cout << s << endl;
    }

    return 0;
}
