/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void findPath(int start1, int start2, int end1, int end2, int &ans, string path) {
    if (start1 == end1 - 1 && start2 == end2 - 1) {
        cout << path << endl;
        ++ans;
    }
    if (start1 >= end1 || start2 >= end2) return;
    findPath(start1 + 1, start2, end1, end2, ans, path + "R");
    findPath(start1, start2 + 1, end1, end2, ans, path + "D");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int m, n, i, j, ans(0); cin >> m >> n >> i >> j;
        string path;
        findPath(m, n, i, j, ans, path);
        cout << "Total possible ways are " << ans << endl;
    }

    return 0;
}

// dp solution
int solve(int i, int j, vector<vector<int>>& dp) {
    if (i < 0 || j < 0) return 0;
    if (i == 0 && j == 0) return 1;
    if (dp[i][j] != -1) return dp[i][j];

    return dp[i][j] = solve(i-1, j, dp) + solve(i, j-1, dp);
}
