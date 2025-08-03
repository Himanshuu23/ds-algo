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
        vector<int> v(n, 0);
        int x = 1;
        for (int i = k; i <= n; i+=k) {
            v[i-1] = x;
            ++x;
        }
        for (int i = 0; i < n; i++) {
            if (!v[i]) { v[i] = x; ++x; }
        }
        for (int i : v) cout << i << " ";
        cout << endl;
    }

    return 0;
}
