/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n, vector<int>& v) {
    if (n == 0) return 0;

    int s(0), e(1), ans(0);

    while (e < n) {
        ans = max(ans, v[e] - v[s]);
        if (v[s] > v[e]) s = e;
        e++;
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

        cout << solve(n, v) << endl;
    }

    return 0;
}
