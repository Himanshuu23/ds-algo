/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool solve(string s) {
    int n = s.size();
    int l(0), r(n - 1);
    while (l < r) {
        while (l < r && !isalnum(s[l])) l++;
        while (l < r && !isalnum(s[r])) r--;
        if (tolower(s[r]) != tolower(s[l])) return false;
        l--; r++;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s; cin >> s;
        puts(solve(s) ? "Yes\n" : "No\n");
    }

    return 0;
}
