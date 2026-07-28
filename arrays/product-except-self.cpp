#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
		int n; cin >> n;
		vector<int> v(n), answer(n, 1);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		
		for (int i = 1; i < n; i++)
			answer[i] = answer[i-1] * v[i-1];

		int suffix = 1;
		for (int i = n - 1; i >= 0; i--) {
			answer[i] *= suffix;
			suffix *= v[i];
		}

		for (int x : answer) cout << x << " ";
    }

    return 0;
}
