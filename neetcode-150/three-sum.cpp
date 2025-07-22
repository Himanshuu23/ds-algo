/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<int>> solve(int n, vector<int>& v) {
    vector<vector<int>> ans;
    sort(v.begin(), v.end());

    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && v[i] == v[i-1]) continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = v[i] + v[l] + v[r];
            if (sum > 0) r--;
            else if (sum < 0) l++;
            else {
                ans.push_back({ v[i], v[l], v[r] });
                while (l < r && v[l] == v[l+1]) l++;
                while (l < r && v[r] == v[r-1]) r--;
                l++; r--;
            }
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
        vector<vector<int>> ans = solve(n, v);
        for (int i = 0; i < ans.size(); i++) {
            for (int n : ans[i]) cout << n << " ";
            cout << endl;
        }
    }

    return 0;
}
