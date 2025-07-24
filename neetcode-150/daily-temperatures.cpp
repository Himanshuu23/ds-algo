/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> solve(int n, vector<int>& v) {
    stack<int> st;
    vector<int> ans(n, 0);

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && v[st.top()] <= v[i]) st.pop();
        if (!st.empty()) ans[i] = st.top() - i;
        st.push(i);
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
        vector<int> ans = solve(n, v);
        for (int i = 0; i < n; i++) cout << ans[i] << " "; cout << endl;
    }

    return 0;
}
