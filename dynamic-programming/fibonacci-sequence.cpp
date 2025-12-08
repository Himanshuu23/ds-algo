/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Memoization (Top Down)
int solve1(int n, vector<int>& v) {
    if (n <= 1) return n;
    if (v[n] != -1) return v[n];
    v[n] = solve1(n-1,v) + solve1(n-2,v);
    return v[n];
}

// Tabulation (Bottom Up) 
int solve2(int n) {
    if (n<=1) return n;
    int a(0), b(1);
    for (int i = 2; i <= n; i++) {
        int temp = b;
        b = a + b;
        a = temp;
    }

    return b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n+1, -1);
        cout << solve1(n, v) << endl;
        cout << solve2(n) << endl;
    }

    return 0;
}
