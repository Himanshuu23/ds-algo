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
        string s; cin >> s;
        bool ff = false;
        int z(0), n(0);
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] != '0' && !ff) {
                ff = true;
                z = s.size() - i - 1;
            } else if (ff && s[i] != '0') n++;
        }

        cout << n + z << endl;
    }

    return 0;
}
