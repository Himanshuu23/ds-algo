#include <bits/stdc++.h>
using namespace std;

// recursion: O(2^n), O(n)
// we just cannot include first and last both together in this version. Hence, we do one dfs including first and one excluding first house.
class Solution {
private:
    int dfs(int i, bool flag, vector<int>& nums) {
        if (i >= nums.size() || (flag && i == nums.size() - 1)) {
            return 0;
        }

        return max(dfs(i + 1, flag, nums), nums[i] + dfs(i + 2, flag, nums));
    }
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        return max(dfs(0, true, nums), dfs(1, false, nums));
    }
};

// optimizing using top down dp: O(n), O(n)
class Solution2 {
private:
    vector<vector<int>> cache;
    int dfs(int i, int flag, vector<int>& nums) {
        if (i >= nums.size() || (flag && i == nums.size() - 1)) {
            return 0;
        }
        if (cache[i][flag] != -1) return cache[i][flag];

        return cache[i][flag] = max(dfs(i + 1, flag, nums), nums[i] + dfs(i + 2, flag, nums));
    }
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];

        cache.resize(nums.size(), vector<int> (2, -1));
        return max(dfs(0, 1, nums), dfs(1, 0, nums));
    }
};

// bottom up dp: O(n), O(n)
class Solution3 {
private:
    int helper(vector<int> nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
        }

        return dp[n-1];
    }
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        return max(helper(vector<int>(nums.begin() + 1, nums.end())), helper(vector<int> (nums.begin(), nums.end() - 1)));
    }
};

// space optimized dp: O(n), O(1)
class Solution4 {
private:
    int helper(vector<int> nums) {
        int rob1 = 0, rob2 = 0;
        for (int num : nums) {
            int temp = max(num + rob1, rob2);
            rob1 = rob2;
            rob2 = temp;
        }
        return rob2;
    }
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) return nums[0];
        return max(helper(vector<int>(nums.begin() + 1, nums.end())), helper(vector<int> (nums.begin(), nums.end() - 1)));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
