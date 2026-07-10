/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll ways(int n) {
    if (n == 1 || n == 2) return n;
    return ways(n-2) + ways(n-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        cout << ways(n) << endl;
    }

    return 0;
}
