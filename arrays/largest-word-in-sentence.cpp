#include <bits/stdc++.h>
using namespace std;

int main() {
    string s, w; getline(cin, s);
    stringstream ss(s);
    int ans(0);
    while (ss >> w) ans = max(ans, (int)w.length());
    cout << ans << endl;
    return 0;
}
