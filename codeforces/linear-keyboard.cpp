/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string keyboard; cin >> keyboard;
        unordered_map<char, int> word;
        for (int i = 0; i < 26; i++) word[keyboard[i]] = i;
        string s; cin >> s;
        int ans(0);
        for (int i = 1; i < s.length(); i++) ans += abs(word[s[i]] - word[s[i-1]]);
        cout << ans << endl;
    }

    return 0;
}
