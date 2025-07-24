/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> solve(int n, vector<int>& v, int k) {
    vector<int> ans;
    priority_queue<pair<int, int>> pq;
    int end(0);

    while (end < n) {
        pq.push({v[end], end});
        if (end >= k-1) {
            while (pq.top().second <= end - k) pq.pop();
            ans.push_back(pq.top().first);
        }
        end++;
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

        vector<int> a = solve(n, v, k);
        for (int b : a) cout << b << " ";
        cout << endl;
    }

    return 0;
}
