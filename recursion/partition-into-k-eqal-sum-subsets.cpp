#include<bits/stdc++.h>
using namespace std;

// exactly same problem as making square with matchsticks just k = 4 there
// brute force - O(k^n)
class Solution {
private:
    bool dfs(int i, vector<int>& nums, vector<int>& subsets, int k) {
        if (i == nums.size()) {
            bool flag = true;
            int value = subsets[0];
            for (int j = 1; j < k; j++) {
                if (subsets[j] != value) {
                    flag = false;
                    break;
                }
            }

            return flag;
        }

        for (int j = 0; j < k; j++) {
            subsets[j] += nums[i];

            if (dfs(i + 1, nums, subsets, k)) {
                return true;
            }

            subsets[j] -= nums[i];
        }

        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        long long sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % k) {
            return false;
        }

        vector<int> subsets(k, 0);

        return dfs(0, nums, subsets, k);
    }
};

// pruning - same complexity but optimizations have good effect - sorting in decreasing order + early break if some side with zero side couldn't be filled - then side with either zero or more than zero can't be filled either 
class Solution2 {
private:
    bool dfs(int i, vector<int>& nums, vector<int>& subsets, int k, int max_length) {
        if (i == nums.size()) {
            return true;
        }

        for (int j = 0; j < k; j++) {
            if (nums[i] + subsets[j] <= max_length) {
                subsets[j] += nums[i];
                if (dfs(i + 1, nums, subsets, k, max_length)) {
                    return true;
                }
                subsets[j] -= nums[i];
            }

            if (subsets[j] == 0) {
                break;
            }
        }

        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        long long sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % k) {
            return false;
        }

        int max_length = sum / k;
        if (*max_element(nums.begin(), nums.end()) > max_length) {
            return false;
        }

        sort(nums.rbegin(), nums.rend());
        vector<int> subsets(k, 0);

        return dfs(0, nums, subsets, k, max_length);
    }
};

// using bitmasking + dp
class Solution3 {
private:
    vector<int> dp;
    int total_sum, n;

    int dfs(int mask, vector<int>& nums, int k) {
        if (mask == 0) return 0;
        if (dp[mask] != INT_MIN) return dp[mask];

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                int result = dfs(mask ^ (1 << i), nums, k);
                if (result >= 0 && result + nums[i] <= total_sum) {
                    dp[mask] = (result + nums[i]) % total_sum;
                    return dp[mask];
                }

                if (mask == (1 << n) - 1) {
                    dp[mask] = -1;
                    return -1;
                }
            }
        }

        dp[mask] = -1;
        return dp[mask];
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        long long sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % k) {
            return false;
        }

        total_sum = sum / k;
        n = nums.size();
        if (*max_element(nums.begin(), nums.end()) > total_sum) {
            return false;
        }

        sort(nums.rbegin(), nums.rend());
        dp.resize(1 << n, INT_MIN);

        return dfs((1 << n) - 1, nums, k) == 0;
    }
};
