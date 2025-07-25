/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// (target - pos) / speed -> time to reach the target (distance / time)

int solve(int t, vector<int>& p, vector<int>& s) {
    int n(p.size());
    vector<pair<int, double>> v;
    for (int i = 0; i < n; i++) v.push_back({p[i], (double)(t-p[i])/s[i]});
    sort(v.rbegin(), v.rend());

    stack<double> st;
    for (auto& c : v) {
        double time = c.second;
        if (st.empty() || time > st.top()) st.push(time);
    }
    return st.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, target; cin >> n >> target;
        vector<int> p(n), s(n);
        for (int i = 0; i < n; i++) cin >> p[i];
        for (int i = 0; i < n; i++) cin >> s[i];
        cout << solve(t, p, s) + 1 << endl;
    }

    return 0;
}
