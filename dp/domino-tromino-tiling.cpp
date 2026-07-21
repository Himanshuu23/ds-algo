#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

// states: 0 -> both rows filled, 1 -> upper row empty, 2 -> lower row empty, 3 -> both rows empty
int solve2(int n) {
	if (n == 0) return 1;
	vector<vector<int>> f(n+1, vector<int> (4, 0));
	f[0][0] = 1; // number of ways to tile nothing complete = 1
	for (int i = 1; i <= n; i++) {
		f[i][0] = (f[i-1][0] + f[i-1][1] + f[i-1][2] + f[i-1][3]) % MOD;
		f[i][1] = (f[i-1][2] + f[i-1][3]) % MOD;
		f[i][2] = (f[i-1][1] + f[i-1][3]) % MOD;
		f[i][3] = (f[i-1][0]) % MOD;
	}

	return f[n][0];
}

int solve(int n) {
    if (n <= 2) return n;
    if (n == 3) return 5;

    vector<int> dp(n+1, 0);
    dp[0] = 1, dp[1] = 1, dp[2] = 2, dp[3] = 5;
    for (int i = 4; i <= n; i++) {
        dp[i] = ((2*dp[i-1]) + (dp[i-3])) % MOD;
    }

    return dp[n];
}
