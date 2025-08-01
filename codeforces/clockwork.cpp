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
        vector<int> v(n);
        bool flag = 0;
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) {
            if (v[i] <= (2*i) || v[i] <= 2*(n-i-1)) flag = 1;
        }
        if (flag) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
