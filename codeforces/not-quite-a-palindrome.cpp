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
        int n, k; cin >> n >> k;
        string s; cin >> s;
        int o(0),z(0);
        for (int i = 0; i < n; i++) (s[i] == '0') ? z++ : o++;
        int mx = (o/2) + (z/2);
        int mn = max(z,o) - n/2;
        puts((k>=mn && k<=mx && (k-mn) % 2 == 0) ? "YES" : "NO");
    }

    return 0;
}
