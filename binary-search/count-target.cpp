/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n, vector<int>& v, int k) {
    return upper_bound(v.begin(), v.end(), k) - lower_bound(v.begin(), v.end(), k);
}

pair<int,int> firstAndLastOccurence(vector<int>&v, int n, int target) {
	int first(-1), last(-1);
	int start = 0, end = n-1;
	while (start <= end) {
		int middle = start + (end - start) / 2;
		int value = v[middle];
		if (value == target) {
			first = middle;
			end = middle - 1;
		} else if (value < target) start = middle + 1;
		else end = middle - 1;
	}

	start = 0, end = n-1;
	while (start <= end) {
		int middle = start + (end - start) / 2;
		int value = v[middle];
		if (value == target) {
			last = middle;
			start = middle + 1;
		} else if (value < target) start = middle + 1;
		else end = middle - 1;
	}

	return {first, last};
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
		auto {first, last} = firstAndLastOccurence(v, n, k);
		if (first == -1) cout << -1 << endl;
		else cout << last - first + 1 << endl;
    }

    return 0;
}
