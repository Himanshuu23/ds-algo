#include <bits/stdc++.h>
using namespace std;

vector<int> longestIncreasingSubsequence(int n, vector<int> &v) {
    vector<int> dp(n, 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (v[j] < v[i]) dp[i] = max(dp[i], dp[j]+1);
        }
    }

    return dp;
}

vector<int> longestDecreasingSubsequence(int n, vector<int> &v) {
    vector<int> dp(n, 1);
    for (int i = n-1; i >= 0; i++) {
        for (int j = n-1; j > i; j--) {
            if (v[i] > v[j]) dp[i] = max(dp[i], 1 + dp[j]);
        }
    }

    return dp;
}

int main() {
    int n, ans(1); cin >> n;
    vector<int> v(n), inc(n), dec(n);

    for (int i = 0; i < n; i++) cin >> v[i];

    inc = longestIncreasingSubsequence(n, v);
    dec = longestDecreasingSubsequence(n, v);

    for (int i = 0; i < n; i++) ans = max(ans, inc[i] + dec[i] - 1);

    cout << ans << endl;

    return 0;
}
