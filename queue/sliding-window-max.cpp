/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> solve(vector<int>& v, int n, int k) {
    deque<int> dq; 
    vector<int> res;

    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front(); // removing the indices outside the window
        while (!dq.empty() && v[dq.back()] < v[i]) dq.pop_back(); // maintaining decreasing order in the deque keeping max at the front
        dq.push_back(i);
        if (i >= k - 1) res.push_back(v[dq.front()]); // once a window is traversed then push its result -> max that is top of the queue to the answer
    } 

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        vector<int> res = solve(v, n, k);
        for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
        cout << endl;
    }

    return 0;
}
