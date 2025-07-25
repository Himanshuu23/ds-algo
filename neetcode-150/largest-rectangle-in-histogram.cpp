/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(vector<int>& v) {
    stack<int> st;
    int ans(0);
    for(int i = 0; i <= v.size(); i++) {
        int curr = (i == v.size()) ? 0 : v[i];
        while (!st.empty() && v[st.top()] >= curr) {
            int h = v[st.top()]; st.pop();
            int w = (st.empty()) ? i : i - st.top() - 1;
            ans = max(ans, h * w);
        }
        st.push(i);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
