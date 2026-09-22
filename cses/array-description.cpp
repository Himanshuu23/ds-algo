#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> v(n);

		const int MOD = 1e9 + 7;

		for (int i = 0; i < n; i++) {
			cin >> v[i];
			--v[i];
		}

		vector<vector<long long>> dp(n, vector<long long> (m));
		for (int i = 0; i < n; i++) {
			if (i) { // not first element -> check for one greater, one lesser, equal conditions
				for (int j = 0; j < m; j++) {
					dp[i][j] = dp[i-1][j]; // equal condition
					if (j) {
						dp[i][j] += dp[i-1][j-1]; // one less condition
					}
					if (j < m - 1) {
						dp[i][j] += dp[i-1][j+1]; // one greater condition
					}
					dp[i][j] %= MOD;
				}
			} else { // for the first element -> base case is all possible values of 'm' is possible
				for (int j = 0; j < m; j++) {
					dp[0][j] = 1;
				}
			}

			if (~v[i]) { // not -1 -> only 1 way to fill non zero elements that is themselves
				for (int j = 0; j < m; j++) {
					if (j ^ v[i]) { // if elements are not equal then no way to fill
						dp[i][j] = 0;
					}
				}
			}
		}	
		
		long long answer = 0;
		for (int i = 0; i < m; i++) {
			answer += dp[n-1][i];
		}

		cout << answer % MOD << '\n';
		}


    return 0;
}
