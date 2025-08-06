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
        int n, ans(-1); cin >> n;
        if (n == 1 || n == 3) cout << "-1\n";
        else if (n%2==0) {
            for (int i = 0; i < n-2; i++) cout << "3";
            cout << "66\n";
        } else {
            for (int i = 0; i < n-5; i++) cout << "3";
            cout << "36366\n";
        }
    }

    return 0;
}
