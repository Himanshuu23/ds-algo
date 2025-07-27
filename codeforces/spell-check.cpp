/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(string s, int n) {
    if (n != 5) return false;
    sort(s.begin(), s.end());
    if (s == "Timru") return true;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        cout << (check(s, n) ? "YES\n" : "NO\n");
    }

    return 0;
}
