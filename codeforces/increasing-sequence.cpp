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
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        for (int i = 0; i < n; i++) {
            if (i == 0) (i == 0 && a[0] == 1) ? b[0] = 2 : b[0] = 1;
            else b[i] = (a[i] == b[i-1]+1) ? b[i-1]+2 : b[i-1]+1;
        }

        cout << b[n-1] << endl;
    }

    return 0;
}
