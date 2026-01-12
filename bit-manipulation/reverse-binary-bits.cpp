/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n) {
	int answer = 0;
	for (int i = 0; i < 32; i++) {
		answer = (answer << 1) | (1 & n);
		n >>= 1;
	}
	
	return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        cout << bitset<32>(n) << endl;
        cout << bitset<32>(solve(n)) << endl;
    }

    return 0;
}
