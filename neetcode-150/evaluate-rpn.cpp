/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            string token = tokens[i];

            if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (st.size() < 2) throw runtime_error("Invalid Expression");
                int op1(st.top()); st.pop();
                int op2(st.top()); st.pop();
                int res;
                if (token == "+") res = op2 + op1;
                else if (token == "-") res = op2 - op1;
                else if (token == "*") res = op2 * op1;
                else res = op2 / op1;
                st.push(res);
            } else st.push(stoi(token));
        }
        if (st.size() != 1) throw runtime_error("Invalid Expression");
            return st.top();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
