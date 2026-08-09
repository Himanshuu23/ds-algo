#include <bits/stdc++.h>
using namespace std;

/*
Problem StatementYou are given an array arr of $n$ positive integers, a binary string state of length $n$, and an integer $m$.state[i] = '1' means arr[i] is available for selection.state[i] = '0' means arr[i] is blocked.You need to construct a sequence $S$ of length $m$ by performing the following process $m$ times:Choose: Pick any available element arr[i] (where state[i] == '1') and append it to $S$.Propagate: Every blocked element that is immediately to the right of an available element becomes available. That is, if state[i-1] == '1', then state[i] becomes '1'.Find the lexicographically largest sequence $S$ of length $m$ that can be generated.Constraints$1 \le n \le 10^5$$1 \le \text{arr}[i] \le 10^9$$1 \le m \le 10^5$state is a binary string of length $n$.Sample CaseInput: arr = [10, 5, 7, 6], state = "0101", m = 2Step 1:Available: $\{5, 6\}$ (at indices 1 and 3)Pick: 6 $\rightarrow S = [6]$State update: Index 1 ('1') unblocks index 2. state becomes "0111".Step 2:Available: $\{5, 7, 6\}$Pick: 7 $\rightarrow S = [6, 7]$Output: [6, 7]
Link - https://leetcode.com/discuss/post/6296159/amazon-oa-question-and-answer-by-anonymo-x6s9/
*/

// brute force - O(N*M), O(M)
vector<int> solve1(vector<int>& v, string s, int n, int m) {
    vector<int> answer;
    while (m--) {
        int mx = INT_MIN;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') mx = max(mx, v[i]);
        }
        answer.push_back(mx);
        for (int i = 0; i < n - 1; i++) {
            if (s[i] == '1' && s[i+1] == '0') {
                s[i+1] = '1';
                i++;
            }
        }
    }

    return answer;
}

// priority queue - NlogN operations + M operations -> O(NlogN + M), O(N + M)
vector<int> solve2(vector<int> v, string s, int n, int m) {
    priority_queue<int, vector<int>> pq;
    vector<int> currently_active;
    vector<int> answer;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            pq.push(v[i]);
            currently_active.push_back(i);
        }
    }
    while (m--) {
        answer.push_back(pq.top());
        vector<int> next_active;
        for (int index : currently_active) {
            if (index + 1 < n && s[index + 1] == '0') {
                s[index + 1] = '1';
                pq.push(v[index + 1]);
                next_active.push_back(index + 1);
            }
        }
        currently_active = next_active;
    }
    return answer;
}

// we don't need pq to have current max element since we can reuse the same elements as well
// O(N+M), O(N+M) - O(N) - max '1' elements can be all and O(M) for answer vector
vector<int> solve3(vector<int>& v, string s, int n, int m) {
    vector<int> answer, current_active;
    int mx = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            current_active.push_back(i);
            mx = max(mx, v[i]);
        }
    }

    while (m--) {
        answer.push_back(mx);
        vector<int> next_active;
        for (int index : current_active) {
            if (index + 1 < n && s[index+1] == '0') {
                s[index+1] = '1';
                mx = max(mx, v[index+1]);
                next_active.push_back(index+1);
            }
        }
        current_active = next_active;
    }
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
        for (int i = 0; i < n; i++) cin >> v[i];
        string s; cin >> s;
        int m; cin >> m;
        vector<int> answer1 = solve1(v, s, n, m);
        for (int x : answer1) cout << x << " ";
        cout << '\n';
        vector<int> answer2 = solve2(v, s, n, m);
        for (int x : answer2) cout << x << " ";
        cout << '\n';
        vector<int> answer3 = solve3(v, s, n, m);
        for (int x : answer3) cout << x << " ";
        cout << '\n';
    }

    return 0;
}
