#include <bits/stdc++.h>
using namespace std;

// asteroid collision - same as LeetCode
// Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/

// using stacks - O(N), O(N)
vector<int> solve(int n, vector<int>& asteroids) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> asteroids(n);
        for (int i = 0; i < n; i++) {
            cin >> asteroids[i];
        }
    }

    return 0;
}
