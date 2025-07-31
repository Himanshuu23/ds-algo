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
        for (int i = 0; i < n; i++) cin >> v[i];
        if (n == 1) { cout << "YES\n"; continue;}
        int sz((n+1)/2), ct(sz-1), x(v[0]);
        sort(v.begin(), v.end());
        if (v[sz] == v[0]) {cout << "YES\n"; continue;}
        for (int i = v.size() - 1; i >= sz - 1; i--) {if (-1*v[i] <= x) ct--; if(!ct) break;}
        if (!ct) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
