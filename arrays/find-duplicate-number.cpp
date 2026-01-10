#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, slow(0), fast(0); cin >> n;
	vector<int> v(n);

	for (int i = 0; i < n; i++) cin >> v[i];

	while (true) {
		slow = v[slow];
		fast = v[v[fast]];
		if (slow == fast) break;
	}

	fast = 0;
	while (true) {
		slow = v[slow];
		fast = v[fast];
		if (slow == fast) return slow;
	}

	return 0;
} 
