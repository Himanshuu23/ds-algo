/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool solve(const string& s1, const string& s2) {
    int n = s1.length(), m = s2.length();
    if (n > m) return false;
    
    unordered_map<char, int> m1, m2;
    int s(0), e(n);

    for (int i = 0; i < n; i++) {
        m1[s1[i]]++; m2[s2[i]]++;
    }
    if (m1 == m2) return true;

    while (e < m) {
        m2[s2[e]]++;

        if (e - s + 1 > n) {
            m2[s2[s]]--;
            if (m2[s2[s]] == 0) m2.erase(s2[s]);
            s++;
        }
        if (m1 == m2) return true;
        e++;
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s1, s2; cin >> s1 >> s2;
        puts(solve(s1, s2) ? "Yes\n" : "No\n");
    }

    return 0;
}
