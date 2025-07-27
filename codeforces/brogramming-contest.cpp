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
        int n; cin >> n;
        string s; cin >> s;
        int curr(0), ans(0);

        for (char c : s) {
            if ((c - '0') != curr) {
                ans++;
                curr = !curr; 
            }
        }
        cout << ans << endl;
    }

    return 0;
}
