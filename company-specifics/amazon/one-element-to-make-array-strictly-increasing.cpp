#include <bits/stdc++.h>
using namespace std;

/*
Given a 0-indexed integer array nums, return true if it can be made strictly increasing after removing at most one element, or false otherwise.An array nums is strictly increasing if nums[i - 1] < nums[i] for all $1 \le i < N$.Input Formatnums: An array/vector of $N$ integers.Output FormatReturn a boolean (true or false).ExamplesExample 1:Input: nums = [1, 2, 10, 5, 7]Output: trueExplanation: By removing 10 at index 2, the remaining array is [1, 2, 5, 7], which is strictly increasing.Example 2:Input: nums = [2, 3, 1, 2]Output: falseExplanation:Remove 3 $\rightarrow$ [2, 1, 2] (Not strictly increasing)Remove 1 $\rightarrow$ [2, 3, 2] (Not strictly increasing)No single removal makes the array strictly increasing.Example 3:Input: nums = [1, 1, 1]Output: falseExplanation: Removing any element leaves [1, 1], which is not strictly increasing.
Link - https://leetcode.com/discuss/post/5931693/amazon-sde-6m-internship-interview-exper-qy1a/
*/

// O(N), O(1)
bool canRemove(int n, vector<int>& v) {
    int operations = 0;
    for (int i = 1; i < n; i++) {
        if (v[i] <= v[i-1]) {
            operations++;
            if (operations > 1) return false;
            // if v[i] cannot replace v[i-1] because v[i] <= v[i-2]
            // we must remove v[i] instead of v[i-1]
            if (i >= 2 && v[i] <= v[i-2]) {
                v[i] = v[i-1]; // simulating removal
            }
        }
    }

    return true;
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

        cout << canRemove(n, v) << '\n';
    }

    return 0;
}
