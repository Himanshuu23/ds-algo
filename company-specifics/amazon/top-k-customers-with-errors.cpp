#include <bits/stdc++.h>
using namespace std;

/*
Amazon's monitoring system logs customer operations. You are given a list of log entries logs and an integer $k$.Each log entry is represented as a string:Successful operations are recorded as "success".Errors are recorded in the format "<customer_id> <error_type>" (e.g., "custA Error 1").Task:Find the top $k$ customers with the highest total count of errors.(Note: "success" logs should be ignored, and duplicate error types from the same customer still count toward that customer's total error count).Sample CaseInput: logs = ["custA Error 1", "custB Error 1", "success", "custA Error 2", "custB Error 1"], k = 2Error Counts:custA: 2 errors (Error 1, Error 2)custB: 2 errors (Error 1, Error 1)Output: ["custA", "custB"] (or ["custB", "custA"] depending on tie-breaker rules)
Link - https://leetcode.com/discuss/post/6333650/amazon-oa-experience-sde1-seattle-by-ano-mnny/
*/

// using priority queue -> O(NL + UlogU), O(UL), N -> number of logs, L is string length, U -> unique customers
vector<string> solve(vector<string>& logs, int k) {
    unordered_map<string, int> mp;
    for (string log : logs) {
        if (log == "success") continue;
        else {
            string person;
            for (char c : log) {
                if (c == ' ') break;
                person += c;
            }
            mp[person]++;
        }
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>> pq;
    for (auto& [person, errors] : mp) {
        pq.push({errors, person});
    }
    vector<string> answer;
    while (k-- && !pq.empty()) {
        answer.push_back(pq.top().second);
        pq.pop();
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        vector<string> v = {"custA Error 1", "custB Error 1", "success", "custA Error 2", "custB Error 1"};
        int k = 2;
        vector<string> answer = solve(v, k);
        for (string p : answer) cout << p << " ";
        cout << '\n';
    }

    return 0;
}
