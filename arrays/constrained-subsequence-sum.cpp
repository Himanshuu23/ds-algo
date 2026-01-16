/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solveDP(int n, vector<int>& v, int k) { // solution using DP - O(nk)
    vector<int> dp = v;
    int mx = INT_MIN;

    for (int i = 0; i < n; i++) {
        for (int j = max(0, i-k); j < i; j++) {
            dp[i] = max(dp[i], v[i] + dp[j]);
            mx = max(dp[i], mx);
        }
    }

    return mx;
}

int solve(int n, vector<int> &v, int k) {
    vector<int> dp = v;
    deque<int> dq;

    for (int i = 0; i < n; i++) {
        if (!dq.empty()) dp[i] += max(0, dp[dq.front()]); // skipping the number's sum if it's negative
        while (!dq.empty() && dp[i] >= dp[dq.back()]) dq.pop_back();
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();
    }
    return *max_element(dp.begin(), dp.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(n, v, k) << endl;
    }

    return 0;
}
