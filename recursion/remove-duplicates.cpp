/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(const string& s, unordered_map<char, int>& mp, int i) {
    if (i == s.size()) {
        cout << '\n';
        return;
    }
    if (mp.find(s[i]) == mp.end()) {
        cout << s[i];
        mp[s[i]]++;
    }
    solve(s, mp, i+1);
}

string removeDup(string s, int i) {
    if (i == s.length()) return s;
    if (count(s.begin(), s.end(), s[i]) > 1) {
        s.erase(i, 1);
        return removeDup(s, i);
    }
    else return removeDup(s, i+1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s; cin >> s;
        cout << removeDup(s, 0) << endl;
    }

    return 0;
}
