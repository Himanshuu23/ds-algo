/*
    author: Himanshuu23
*/
#include <bits/stdc++.h> 
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        unordered_map<int, int> mp;
        priority_queue<pair<int, int>, vector<pair<int, int>>> pq;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            mp[x]++;
        }

        for (auto& [key, value] : mp) pq.push({value, key});
        while (k--) {
            cout << pq.top().second << " ";
            pq.pop();
        }
        cout << '\n';
    }

    return 0;
}
