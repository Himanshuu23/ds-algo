/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// (target - pos) / speed -> steps to reach the target

int solve(int t, vector<int>& p, vector<int>& s) {
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, target; cin >> n >> target;
        vector<int> p(n), s(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) cin >> s[i];
        cout << solve(t, p, s) + 1 << endl;
    }

    return 0;
}
