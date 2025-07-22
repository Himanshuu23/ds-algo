/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(int n, vector<int>& v) {
    unordered_set<int> mp(v.begin(), v.end());
    int ans = 0;

    for (int x : mp) {
        if (!mp.count(x - 1)) {
            int curr = 1;
            while (mp.count(x + curr)) {
                curr++;
            }
            ans = max(ans, curr);
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(n, v) << endl;
    }

    return 0;
}
