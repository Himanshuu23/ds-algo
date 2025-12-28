#include<bits/stdc++.h>
using namespace std;

void solve(string s, int open, int close, vector<string>& answer) {
    if (open == 0 && close == 0) {
        answer.push_back(s);
        return;
    }

    if (open == close) {
        string curr = s;
        curr.push_back('(');
        solve(curr, open-1, close, answer);
    }

    else if (open == 0) {
        string curr = s;
        curr.push_back(')');
        solve(curr, open, close-1, answer);
    }

    else if (close == 0) {
        string curr = s;
        curr.push_back('(');
        solve(curr, open-1, close, answer);
    }

    else {
        string curr1 = s, curr2 = s;
        curr1.push_back('(');
        curr2.push_back(')');
        solve(curr1, open-1, close, answer);
        solve(curr2, open, close-1, answer);
    }
}
