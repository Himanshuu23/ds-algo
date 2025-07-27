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
        int n, e(0), o(0); cin >> n;
        for (int i = 0; i < n; i++) {
            int temp; cin >> temp;
            if (i % 2 == 0 && temp % 2) e++;
            if (i % 2 && temp % 2 == 0) o++;
        }
        
        (e != o) ? cout << -1 << '\n' : cout << e << '\n';
    }

    return 0;
}
