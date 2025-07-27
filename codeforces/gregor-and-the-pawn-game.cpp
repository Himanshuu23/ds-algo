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
        string g, e; cin >> e >> g;
        vector<bool> used(n, false);
        int res(0);

        for (int i = 0; i < n; i++) {
            if (g[i] == '1') {
                if (e[i] == '0') res++;
                else {
                    if (i > 0 && e[i-1] == '1' && !used[i-1]) {
                        used[i-1] = true; res++;
                    } else if (i + 1 < n && e[i+1] == '1' && !used[i+1]) {
                        used[i+1] = true; res++;
                    }
                }
            }
        }

        cout << res << endl;
    }

    return 0;
}
