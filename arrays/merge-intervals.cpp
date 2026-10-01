#include<bits/stdc++.h>
using namespace std;

// O(n^3), O(n)
vector<vector<int>> bruteForce(vector<vector<int>>& intervals) {
    vector<vector<int>> result = intervals;
    bool merged = true;

    while (merged) {
        merged = false;
        for (int i = 0; i < result.size() && !merged; i++) {
            for (int j = i + 1; j < result.size(); j++) {
                if (result[i][0] <= result[j][1] && result[j][0] <= result[i][1]) { // overlaps
                    result[i][0] = min(result[i][0], result[j][0]);
                    result[i][1] = max(result[i][1], result[j][1]);
                    result.erase(result.begin() + j);
                    merged = true; // intervals skipped earlier may overlap now because of this new merge - so starting again from i = 0
                    break;
                }
            }
        }
    }

    return result;
}

// O(nlogn), O(n)
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    int n = intervals.size();
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
