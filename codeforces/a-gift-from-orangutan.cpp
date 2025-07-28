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
        ll n; cin >> n;
        int mx(INT_MIN), mn(INT_MAX);
        for (int i = 0; i < n; i++) {
            int temp; cin >> temp;
            mx = max(mx, temp); mn = min(mn, temp);
        }
        cout << ((n-1)*(mx-mn)) << endl;
    }

    return 0;
}
