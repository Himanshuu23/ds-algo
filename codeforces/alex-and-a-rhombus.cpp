/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n) {
    if (n == 1) return 1;
    return ((n-1)*4) + solve(n-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        int n; cin >> n;
        int ans = solve(n);
        cout << ans << endl;

    return 0;
}
