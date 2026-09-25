#include <bits/stdc++.h>
using namespace std;

// recursion: O(2^n), O(n)
class Solution {
private:
    int dfs(vector<int>& nums, int i) {
        if (i >= nums.size()) {
            return 0;
        }

        return max(dfs(nums, i + 1), nums[i] + dfs(nums, i + 2));
    }
public:
    int rob(vector<int>& nums) {
        return dfs(nums, 0);
    }
};

// optimizing previous solution with top down dp: O(n), O(n)
class Solution2 {
private:
    vector<int> cache;
    int dfs(vector<int>& nums, int i) {
        if (i >= nums.size()) {
            return 0;
        }
        if (cache[i] != -1) return cache[i];

        return cache[i] = max(dfs(nums, i + 1), nums[i] + dfs(nums, i + 2));
    }
public:
    int rob(vector<int>& nums) {
        cache.assign(nums.size(), -1);
        return dfs(nums, 0);
    }
};

// using bottom up dp: O(n), O(n)
class Solution3 {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
        }
        return dp[n-1];
    }
};

// dp but space optimized: O(n), O(1)
// since we don't need whole array: since for current array we depend on just value i - 1 and i - 2 that is house before current i.e. previous and house before previous - there best results - so instead we can just store those result in two variables.
class Solution4 {
public:
    int rob(vector<int>& nums) {
        int rob1 = 0, rob2 = 0; // rob1 -> best house upto i - 2 and rob2 upto i - 1 (previous)
        for (int num : nums) {
            int temp = max(num + rob1, rob2);
            rob1 = rob2;
            rob2 = temp;
        }

        return rob2;
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
