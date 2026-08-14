#include <bits/stdc++.h>
using namespace std;

/*
Given an array of intervals where intervals[i] = [start_i, end_i], merge all overlapping intervals, and return an array of non-overlapping intervals that cover all the intervals in the input.Two intervals [a, b] and [c, d] overlap if c <= b (assuming a <= c).Input Formatintervals: A 2D array/vector of size $N \times 2$, where each row represents an interval [start, end].Output FormatReturn a 2D array/vector representing the merged intervals sorted by start time.ExamplesExample 1:Input: intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]Output: [[1, 6], [8, 10], [15, 18]]Explanation: Since intervals [1, 3] and [2, 6] overlap, they merge into [1, 6].Example 2:Input: intervals = [[1, 4], [4, 5]]Output: [[1, 5]]Explanation: Intervals [1, 4] and [4, 5] are considered overlapping at point 4.
Link - https://leetcode.com/discuss/post/5931693/amazon-sde-6m-internship-interview-exper-qy1a/
*/

vector<vector<int>> mergeIntervals(int n, vector<vector<int>>& intervals) {
    vector<vector<int>> result;
    sort(intervals.begin(), intervals.end());
    for (int i = 0; i < n; i++) {
        if (result.empty() || result.back()[1] < intervals[i][0]) {
            result.push_back(intervals[i]);
        } else {
            result.back()[1] = max(result.back()[1], intervals[i][1]);
        }
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<vector<int>> intervals(n, vector<int> (2));
        for (int i = 0; i < n; i++) {
            cin >> intervals[i][0] >> intervals[i][1];
        }
        vector<vector<int>> answer = mergeIntervals(n, intervals);
        for (int i = 0; i < answer.size(); i++) {
            for (int j = 0; j < 2; j++) {
                cout << answer[i][j] << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}
