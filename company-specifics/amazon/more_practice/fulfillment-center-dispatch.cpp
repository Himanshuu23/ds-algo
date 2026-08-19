#include <bits/stdc++.h>
using namespace std;

/*
Amazon is optimizing its automated conveyor belt system in a fulfillment center. You are given an array weights of size $n$, representing the weight of $n$ packages placed in sequence on a conveyor belt.A single dispatch batch consists of selecting a contiguous subarray of packages such that the difference between the heaviest package and the lightest package in that batch is at most $k$.The efficiency score of a batch is defined as the number of packages in that subarray (its length).Return the maximum efficiency score achievable for any valid dispatch batch.Input Formatweights: An array of $n$ integers.k: An integer representing the maximum allowed weight difference.Output FormatReturn a single integer representing the maximum possible length of a valid contiguous subarray.Constraints$1 \le n \le 10^5$$1 \le \text{weights}[i] \le 10^9$$0 \le k \le 10^9$Example 1Input:weights = [10, 1, 2, 4, 7]k = 5Output: 3Explanation:Subarray [1, 2, 4] has $\max = 4$, $\min = 1$. Difference = $4 - 1 = 3 \le 5$. Length = 3.Subarray [2, 4, 7] has $\max = 7$, $\min = 2$. Difference = $7 - 2 = 5 \le 5$. Length = 3.No contiguous subarray of length 4 satisfies the condition. Maximum length is 3.Example 2Input:weights = [8, 8, 8, 8]k = 0Output: 4Explanation:The entire array [8, 8, 8, 8] has $\max = 8$, $\min = 8$. Difference = $8 - 8 = 0 \le 0$. Length = 4.
*/

//O(NlogN), O(N)
int getMaximumEfficiency(int n, vector<int>& weights, int k) {
    multiset<int> window;
    int answer = 0;
    int start = 0, end = 0;
    while (end < n) {
        window.insert(weights[end]);
        while (*window.rbegin() - *window.begin() > k) {
            window.erase(window.find(weights[start]));
            start++;
        }
        answer = max(answer, end - start + 1);
        end++;
    }
    return answer;
}

// O(N), O(N)
int getMaximumEfficiency2(int n, vector<int>& weights, int k) {
    deque<int> max_dq, min_dq;
    int answer = 0;
    int start = 0, end = 0;
    while (end < n) {
        while (!max_dq.empty() && weights[max_dq.back()] <= weights[end]) max_dq.pop_back();
        while (!min_dq.empty() && weights[min_dq.back()] >= weights[end]) min_dq.pop_back();
        max_dq.push_back(end);
        min_dq.push_back(end);
        while (weights[max_dq.front()] - weights[min_dq.front()] > k) {
            start++;
            if (max_dq.front() < start) max_dq.pop_front();
            if (min_dq.front() < start) min_dq.pop_front();
        }
        answer = max(answer, end - start + 1);
        end++;
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

        cout << getMaximumEfficiency(n, v, k) << '\n';
    }

    return 0;
}
