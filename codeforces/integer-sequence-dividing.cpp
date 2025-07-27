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
        n %= 4;
        if (n==0 || n==3) cout << 0 << endl;
        else cout << 1 << endl;
        
    return 0;
}
