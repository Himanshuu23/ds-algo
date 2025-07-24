/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string solve(string& s, string& t) {
    int n(s.size()), m(t.size());
    if (n < m) return "";

    unordered_map<char, int> m1, m2;
    for (int i = 0; i < m; i++) m2[t[i]]++;
    int st(0), e(0), ml(INT_MAX), ms(0), need(m2.size()), have(0);
    while (e < n) {
        char c = s[e];
        m1[c]++;
        if (m2.count(c) && m2[c] == m1[c]) have++;
        while (have == need) {
            if (e - st + 1 < ml) {
                ml = e - st + 1;
                ms = st;
            }

            char toRemove = s[st];
            m1[toRemove]--;

            if (m2.count(toRemove) && m1[toRemove] < m2[toRemove]) have--;
            st++;
        }
        e++;
    }

    return (ml == INT_MAX) ? "" : s.substr(ms, ml);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s, t; cin >> s >> t;
        cout << solve(s, t) << endl;
    }

    return 0;
}
