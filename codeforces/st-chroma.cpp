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
        int n, x; cin >> n >> x;
        if (n == 1) { cout << 0 << endl; continue; }
        for (int i = 0; i < n; i++) if (i != x) cout << i << " ";
        (n != x) ? cout << x << endl : cout << endl;
    }

    return 0;
}
