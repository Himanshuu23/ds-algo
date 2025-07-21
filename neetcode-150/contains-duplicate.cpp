/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool solve(int n, vector<int>& v) {
    if (n <= 1) return false;
    unordered_map<int, int> mp;

    for (int i = 0; i < n; i++) {
        if (mp[v[i]] == 1) return true;
        else mp[v[i]]++;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n);
        
        for (int i = 0; i < n; i++) cin >> v[i];
        solve(n, v) ? cout << "Yes" : cout << "No";
        cout << '\n';
    }

    return 0;
}
