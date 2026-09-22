#include <bits/stdc++.h>
using namespace std;

/*
This problem is to practice Array Description on CSES - (a variation of that problem)
You have an array of n integers, each between 1 and m. This time, the constraint is different: each element must be strictly greater than or equal to the previous element, OR at most 2 less than the previous element (i.e., a[i] >= a[i-1] OR a[i-1] - a[i] <= 2).
In other words, from position i-1 to i, you can:
go up by any amount (or stay the same), OR
go down by at most 2
Some values are given, some are unknown (denoted 0). Count the number of valid arrays satisfying the description, modulo 10^9 + 7.
Input:
n m
x1 x2 ... xn
Constraints: 1 ≤ n ≤ 10^5, 1 ≤ m ≤ 100, 0 ≤ xi ≤ m
*/
// the given constraints a[i-1] - a[i] <= 2 -> a[i] >= a[i-1] - 2 which falls inside the first condition a[i] >= a[i-1] means we can club them into same condition that is a[i] >= a[i-1] - 2 => a[i-1] <= a[i] + 2, hence we can just find the total ways in i-1 using prefix sum and no explicit condition checks are needed for 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
		const int MOD = 1e9 + 7;
		int n, m; cin >> n >> m;
		vector<long long> v(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
			--v[i];
		}

		vector<vector<long long>> dp(n, vector<long long> (m));
		for (int i = 0; i < n; i++) {
			if (i) {
				vector<long long> prefix(m);
				prefix[0] = dp[i-1][0];
				for (int k = 1; k < m; k++) {
					prefix[k] = (prefix[k-1] + dp[i-1][k]) % MOD;
				}
				for (int j = 0; j < m; j++) { // all values of i such that a[i-1] <= a[i] + 2
					dp[i][j] = prefix[min(j + 2, m - 1)];
				}
			} else {
				for (int j = 0; j < m; j++) {
					dp[i][j] = 1;
				}
			}

			if (~v[i]) {
				for (int j = 0; j < m; j++) {
					if (j ^ v[i]) {
						dp[i][j] = 0;
					}
				}
			}
		}

		long long answer = 0;
		for (int j = 0; j < m; j++) {
			answer += dp[n-1][j];
		}

		cout << answer % MOD << '\n';
    }

    return 0;
}
