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
        int n, amt; cin >> n >> amt;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        vector<int> dp(amt+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amt; i++) {
            for (int x : v) {
                if (i-x>=0) dp[i] = min(dp[i], dp[i-x]+1);
            }
        }
        cout << (dp[amt] == INT_MAX ? -1 : dp[amt]) << endl;
    }

    return 0;
}
