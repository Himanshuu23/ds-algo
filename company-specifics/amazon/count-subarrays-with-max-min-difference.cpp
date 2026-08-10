#include <bits/stdc++.h>
using namespace std;

/*
Given an integer array nums and an integer k, find the total number of contiguous non-empty subarrays such that the difference between the maximum element and the minimum element in the subarray is at most k.Formally, count all pairs of indices $(i, j)$ with $0 \le i \le j < n$ such that:$$\max(\text{nums}[i \dots j]) - \min(\text{nums}[i \dots j]) \le k$$TaskReturn the total count of valid subarrays as a long long integer.Constraints$1 \le \text{nums.length} \le 10^5$$1 \le \text{nums}[i] \le 10^9$$0 \le k \le 10^9$Sample CasesExample 1:Input: nums = [5, 4, 2, 4], k = 2Output: 8Explanation:Length 1: [5], [4], [2], [4] (4 valid)Length 2: [5, 4] ($\text{max}-\text{min} = 1$), [4, 2] ($2$), [2, 4] ($2$) (3 valid)Length 3: [4, 2, 4] ($\text{max}-\text{min} = 2$) (1 valid)Length 4: [5, 4, 2, 4] ($\text{max}-\text{min} = 3 > 2$) (Invalid)Total: $4 + 3 + 1 = 8$
Link - https://leetcode.com/discuss/post/2180363/amazon-oa-by-anonymous_user-xrnn/
*/

// using sliding window + two monotonic deque (one for min, one for max) - O(N), O(N)
long long solve(vector<int>& v, int k) {
    deque<int> min_q, max_q;
    int left = 0;
    long long answer = 0;
    for (int right = 0; right < v.size(); right++) {
        while (!min_q.empty() && v[min_q.back()] >= v[right]) {
            min_q.pop_back();
        }
        min_q.push_back(right);
        while (!max_q.empty() && v[max_q.back()] <= v[right]) {
            max_q.pop_back();
        }
        max_q.push_back(right);
        while (v[max_q.front()] - v[min_q.front()] > k) {
            left++;
            if (max_q.front() < left) max_q.pop_front();
            if (min_q.front() < left) min_q.pop_front();
        }

        answer += (right - left + 1);
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        cout << solve(v, k) << '\n';
    }

    return 0;
}
