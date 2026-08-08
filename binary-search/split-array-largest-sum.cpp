#include<bits/stdc++.h>
using namespace std;

// O(n*2^n), O(n) - recursion and using dp memoization - O(k*n^2), O(k*n) - since now each state is calculated just once i.e for each n elements doing -> checking k splits on n elements
class Solution {
    int dfs(vector<int>& nums, int i, int m, int n, vector<vector<int>>& dp) {
        if (i == n) {
            return m == 0 ? 0 : INT_MAX;
        }
        if (m == 0) return INT_MAX;
        if (dp[i][m] != -1) return dp[i][m];
        int answer = INT_MAX, current_sum = 0;
        for (int j = i; j <= n - m; j++) {
            current_sum += nums[j];
            answer = min(answer, max(current_sum, dfs(nums, j + 1, m - 1, n, dp)));
        }

        return dp[i][m] = answer;
    }
public:
    int splitArray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int> (k+1, -1));
        return dfs(nums, 0, k, n, dp); 
    }
};

// binary search - O(nlogs), O(1), s -> sum of elements
class Solution1 {
    bool canSplit(vector<int>& nums, int k, int maximum_sum) {
        int subarrays = 1, current_sum = 0;
        for (int num : nums) {
            current_sum += num;
            if (current_sum > maximum_sum) {
                ++subarrays;
                if (subarrays > k) return false;
                current_sum = num;
            }
        }
        return true;
    }
public:
    int splitArray(vector<int>& nums, int k) {
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        int answer = right;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (canSplit(nums, k, middle)) {
                answer = middle;
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }

        return answer;
    }
};
