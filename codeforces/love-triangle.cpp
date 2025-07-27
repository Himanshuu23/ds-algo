/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        int n; cin >> n;
        vector<int> v(n);
        bool flag = false;
        for (int i = 0; i < n; i++) { cin >> v[i]; v[i]--; }

        for (int i = 0; i < n - 1; i++) {
            if (v[v[v[i]]] == i) {
                flag = true; break;
            }
        }

        puts(flag ? "YES" : "NO");

    return 0;
}
