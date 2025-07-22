/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<int, int> solve(int n, vector<int>& v, int target) {
    int l(0), r(n - 1);
    while (l < r) {
        int sum = v[l] + v[r];
        if (sum == target) return {l+1, r+1};
        else if (sum > target) r--;
        else l++;
    }

    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, target; cin >> n >> target;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        pair<int, int> ans = solve(n, v, target);
        cout << ans.first << " " << ans.second << endl;
    }

    return 0;
}
