/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// using dequeue -> best approach O(n)

vector<int> solve(int n, vector<int>& v, int k) {
    vector<int> ans;
    deque<int>dq;
    
    for (int i = 0; i < n; i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while(!dq.empty() && v[dq.back()] < v[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k-1) ans.push_back(v[dq.front()]);
    }

    return ans;
}

// using heap -> sliding window -> nlogk
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        vector<int> v(n), ans;
        priority_queue<pair<int, int>> mh;
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) {
            mh.push({v[i], i});
            while (!mh.empty() && mh.top().second <= i - k) mh.pop();
            if (i >= k - 1) ans.push_back(mh.top().first);
        }
        for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
        cout << endl;
    }

    return 0;
}
