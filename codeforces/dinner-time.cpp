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
        int n, m, p, q; cin >> n >> m >> p >> q;
        if (!(n%p) && (n/p)*q != m) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
