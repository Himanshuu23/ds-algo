#include <bits/stdc++.h>
using namespace std;

// same as in (arrays)
// Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/
// O(n), O(n)
vector<int> maxForMinWindows(int n, vector<int>& v) {
    vector<int> result(n+2, 0);
    vector<int> left(n+1, -1);
    vector<int> right(n+1, n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && v[st.top()] >= v[i]) st.pop();
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && v[st.top()] >= v[i]) st.pop();
        if (!st.empty()) right[i] = st.top();
        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        int length = right[i] - left[i] - 1;
        result[length] = max(result[length], v[i]);
    }

    for (int i = n - 1; i >= 1; i--) {
        result[i] = max(result[i], result[i+1]);
    }

    vector<int> answer(result.begin() + 1, result.begin() + n + 1);
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        vector<int> answer = maxForMinWindows(n, v);
        for (int x : answer) {
            cout << x << " ";
        }
        cout << '\n';
    }

    return 0;
}
