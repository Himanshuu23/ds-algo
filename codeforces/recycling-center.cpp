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
        int n,c,mt(1),ans(0); cin >> n >> c;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(), v.end());
        for (int num : v) {
            if (num*mt > c) ans++;
            mt*=2;
        }
        cout << ans << endl;
    }

    return 0;
}
