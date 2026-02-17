/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// patience sorting - nlogn
int lengthOfLIS(vector<int>& v) {
	int n = v.size();
	vector<int> tails;
	for (int x : v) {
		auto it = lower_bound(tails.begin(), tails.end(), x);
		if (it == tails.end()) tails.push_back(x);
		else *it = x;
	}

	return tails.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int>v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(n, v) << endl;
    }

    return 0;
}
