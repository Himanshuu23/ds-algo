/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        string s; cin >> s;
        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());

        if (s < rev_s || (k >= 1 && *min_element(s.begin(), s.end()) != *max_element(s.begin(), s.end()))) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
