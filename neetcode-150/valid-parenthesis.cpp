/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool checkMyCorresponding(char c, char t) {
    if (c == ')') return t == '(';
    else if (c == '}') return t == '{';
    else return t == '[';
}

bool solve(string s) {
    stack<char> st;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') st.push(c);
        else {
            if (st.empty() || !checkMyCorresponding(c, st.top())) return false; 
            st.pop();
        }
    }

    if (!st.empty()) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        string s; cin >> s;
        cout << solve(s) << endl;
    }

    return 0;
}
