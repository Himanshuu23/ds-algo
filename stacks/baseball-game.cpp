#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calPoints(vector<string>& operations) {
        stack<int> st;
        int sum = 0;
        for (string c : operations) {
            if (c == "+") {
                int top = st.top(); st.pop();
                int newTop = st.top() + top;
                st.push(top);
                st.push(newTop);
                sum += newTop;
            } else if (c == "C") {
                sum -= st.top();
                st.pop();
            } else if (c == "D") {
                st.push(2 * st.top());
                sum += st.top();
            } else {
                st.push(stoi(c));
                sum += st.top();
            }
        }

        return sum;
    }
};
