/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool solve(vector<vector<int>>& v, int t) {
    int r(0), c(v[0].size() - 1);
    while (r < v.size() && c >= 0) {
        if (v[r][c] == t) return true;
        else if (v[r][c] > t) c--;
        else r++;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
