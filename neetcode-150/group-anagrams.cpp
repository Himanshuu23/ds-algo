/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<vector<string>> solve(const vector<string>& w) {
    unordered_map<string, vector<string>> mp;
    vector<vector<string>> ans;

    for (string c : w) {
        string key = c;
        sort(key.begin(), key.end());
        mp[key].push_back(c);
    }
    for (auto& [key, group] : mp) ans.push_back(group);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<string> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        vector<vector<string>> ans = solve(v);
        for (int i = 0; i < ans.size(); i++) {
            cout << i + 1 << " : ";
            for (auto& w : ans[i]) {
                cout << w << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
