/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> solve(int n, vector<int>& v) {
    vector<int> ans(n, 1);
    
    int prefix = 1;
    for (int i = 0; i < n; i++) {
        ans[i] *= prefix;
        prefix *= v[i];
    }

    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
        ans[i] *= suffix;
        suffix *= v[i];
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        vector<int> ans = solve(n, v);
        for (int n : ans) cout << n << " ";
        cout << endl;
    }

    return 0;
}
