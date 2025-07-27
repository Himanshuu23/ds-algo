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
        int n; cin >> n;bool flag = true;
        while (n--) {
            int t; cin >> t;
            if (t == 1) flag = false;
            else continue;
        }

        puts(flag ? "EASY" : "HARD");
    }

    return 0;
}
