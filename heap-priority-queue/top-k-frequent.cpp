/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> solve(int n, const vector<int>& v, int k) {
    unordered_map<int, int> mp;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> ans;

    for (int i = 0; i < n; i++) mp[v[i]]++;
    for (auto& [key, val] : mp) {
        pq.push({val, key});
        if (pq.size() > k) pq.pop();
    }

    while (!pq.empty()) {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];

        vector<int> ans = solve(n, v, k);
        for (int n : ans) cout << n << " ";
        cout << endl;
    }

    return 0;
}
