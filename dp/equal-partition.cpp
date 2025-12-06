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
        int n, s(0); cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            s += v[i];
        }
        s /= 2;
        vector<int> dp(s+1, 0);
        dp[0] = 1;
        for (int x : v) {
            for (int i = s; i >= x; i--) {
                if (dp[i-x] == 1) dp[i] = 1;
            }
        }

        (dp[s] == 1) ? cout << "Yes\n" : cout << "No\n";
    }

    return 0;
}
