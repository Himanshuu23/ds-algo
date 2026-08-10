#include <bits/stdc++.h>
using namespace std;

/*
Amazon's financial analysts calculate a stock's $k$-consistency score to measure how consistently a stock yields identical daily percentage returns.You are given an array stockPrices of size $n$, where stockPrices[i] represents the percentage return delivered on the $i$-th day, and an integer $k$.In a single operation, you can remove/omit at most $k$ elements from stockPrices. When elements are removed, the remaining parts of the array join together to form a single continuous sequence.Find the maximum length of a contiguous subarray containing identical returns after deleting at most $k$ elements.Input Parameters:stockPrices: An array of integers representing daily returns (can be positive, zero, or negative).k: An integer representing the maximum allowable deletions.Sample CaseSample 1Input: stockPrices = [1, 2, 1, 1, 3, 1], k = 2Output: 4Explanation:If you remove stockPrices[1] (value 2) and stockPrices[4] (value 3), the array becomes [1, 1, 1, 1].The maximum number of contiguous identical elements is 4.
Link : https://leetcode.com/discuss/post/6333650/amazon-oa-experience-sde1-seattle-by-ano-mnny/
*/

// using sliding window -> O(N), O(N)
int solve(vector<int>& stockPrices, int k) {
    if (stockPrices.empty()) return 0;

    unordered_map<int, vector<int>> positions;
    for (int i = 0; i < stockPrices.size(); i++) {
        positions[stockPrices[i]].push_back(i);
    }

    int answer = 0;
    for (auto& [x, indices] : positions) {
        int left = 0;
        for (int right = 0; right < indices.size(); right++) {
            int deletions = (indices[right] - indices[left]) - (right - left);
            while (deletions > k) {
                left++;
                deletions = (indices[right] - indices[left]) - (right - left);
            }

            answer = max(answer, right - left + 1);
        }
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
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        int k; cin >> k;
        cout << solve(v, k) << '\n';
    }

    return 0;
}
