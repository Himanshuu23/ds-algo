#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        for (int x : asteroids) {
            while (!st.empty() && x < 0 && st.top() > 0) {
                int difference = x + st.top();
                if (difference < 0) {
                    st.pop();
                } else if (difference > 0) {
                    x = 0;
                } else {
                    x = 0;
                    st.pop();
                }
            }
            if (x != 0) st.push(x);
        }

        vector<int> answer;
        while (!st.empty()) {
            answer.push_back(st.top());
            st.pop();
        }
        reverse(answer.begin(), answer.end());
        return answer;
    }
};
