#include<bits/stdc++.h>
using namespace std;

// using backtracking - backtracking function takes current subset and index -> find the xor sum of this subset, add to the result, for each remaining element -> add it to subset, recursively call for next index - to consider subsets including this element, remove the element from the subset to consider subsets excluding this element - O(n*2^n), O(n)
class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int result = 0;
        vector<int> subset;

        function<void(int)> backtrack = [&](int i) {
            int xor_sum = 0;
            for (int num : subset) xor_sum ^= num;
            result += xor_sum;

            for (int j = i; j < nums.size(); j++) {
                subset.push_back(nums[j]);
                backtrack(j+1);
                subset.pop_back();
            }
        };

        backtrack(0);
        
        return result;
    }
};

// recursion - 2^n : for each element two choices (include, exclude)
class Solution2 {
private:
    int dfs(vector<int>& nums, int i, int total) {
        if (i == nums.size()) {
            return total;
        }

        return dfs(nums, i + 1, total ^ nums[i]) + dfs(nums, i + 1, total);
    }
public:
    int subsetXORSum(vector<int>& nums) {
        return dfs(nums, 0, 0);
    }
};

// Bit Manipulation - every subset can be represent with a bitmask of 2^n size (for each element -> (include, exclude) -> so for each mask 0 to 2^n-1 if ith bit is set - we consider that element in the current xor_sum result - O(n*2^n), O(1)
class Solution3 {
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int result = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            int xor_sum = 0;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    xor_sum ^= nums[i];
                }
            }
            result += xor_sum;
        }

        return result;
    }
};

// O(n), O(1) - each element contributes to exactly half of the subsets (exclude, include) - so when we take xor of all elements at the end we get all those bits in xor_sum set that would have atleast one element in the subset, now each element contribution = its value * 2*(n-1), so total subsets = 2^n and half would be 2^(n-1)
class Solution4 {
public:
    int subsetXORSum(vector<int>& nums) {
        int xor_sum = 0;
        int n = nums.size();
        for (int num : nums) {
            xor_sum |= num;
        }

        return (xor_sum) << (n - 1);
    }
};
