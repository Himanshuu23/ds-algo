#include <bits/stdc++.h>
using namespace std;

/*
Given an overall time window defined by start and end, and a list of booked meetings (where each meeting is an interval [s_i, e_i]), find all the free time slots where no meetings are scheduled within [start, end].
Input Parameters:
start: An integer representing the start of the overall time period.
end: An integer representing the end of the overall time period.
meetings: A list of intervals [s_i, e_i] representing busy time slots.
Sample Case
Input: start = 0, end = 12, meetings = [[1, 3], [5, 6], [10, 12]]
Output: [[0, 1], [3, 5], [6, 10]]
Explanation:
Free from 0 to 1 (before 1st meeting)
Free from 3 to 5 (between 1st & 2nd meeting)
Free from 6 to 10 (between 2nd & 3rd meeting)
Link : https://leetcode.com/discuss/post/6333650/amazon-oa-experience-sde1-seattle-by-ano-mnny/
*/

// O(nlogn), O(n)
vector<pair<int, int>> solve(int start, int end, vector<pair<int, int>>& meets) {
    sort(meets.begin(), meets.end());
    vector<pair<int, int>> free;

    int current = start;
    for (auto& [s, e] : meets) {
        if (s > current) {
            free.push_back({ current, s });
        }

        current = max(current, e);
    }

    if (current < end) {
        free.push_back({ current, end });
    }

    return free;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int start, end; 
        cin >> start >> end;
        int n; cin >> n;
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i].first >> v[i].second;
        }
        vector<pair<int, int>> answer = solve(start, end, v);
        for (auto& [x, y] : answer) {
            cout << x << " " << y << '\n';
        }
    }

    return 0;
}
