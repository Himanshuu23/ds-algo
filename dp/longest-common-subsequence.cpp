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
        int n1, n2; cin >> n1 >> n2;
        string a, b; cin >> a >> b;

        vector<vector<int>> dp(n1+1, vector<int> (n2+1, 0));

        for (int i = n1-1; i >= 0; i--) {
            for (int j = n2-1; j >= 0; j--) {
                if (a[i] == b[j]) dp[i][j] = 1 + dp[i+1][j+1];
                else dp[i][j] = max(dp[i+1][j], dp[i][j+1]);
            }
        }

        cout << dp[0][0] << endl;
    }

    return 0;
}
