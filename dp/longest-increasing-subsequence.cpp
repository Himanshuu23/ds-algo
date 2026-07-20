/*
    author: Himanshuu23
*/
#include <bits/stdc++.h> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}

		int answer = 1;
		vector<int> dp(n, 1);
		for (int i = 1; i < n; i++) {
			int mx = -1;
			for (int j = 0; j < i; j++) {
				if (v[i] > v[j]) mx = max(mx, dp[j]);
			}
			dp[i] = max(dp[i], 1 + mx);
			answer = max(answer, dp[i]);
		}

		cout << answer << '\n';
	}

    return 0;
}
