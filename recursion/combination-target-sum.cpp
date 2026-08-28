#include <bits/stdc++.h>
using namespace std;

// recursion + backtracking - O(2 ^ (target/m)), m -> min value in the nums, O(target/m)
// not moving to next index until sum < target -> trying out multiple times
class Solution {
    void dfs(const vector<int>& nums, int target, int i, int sum, vector<int>& subset, vector<vector<int>>& result) {
        if (sum == target) {
            result.push_back(subset);
            return;
        }
        if (i == nums.size() || sum > target) {
            return;
        }

        subset.push_back(nums[i]);
        dfs(nums, target, i, sum + nums[i], subset, result);
        subset.pop_back();
        dfs(nums, target, i + 1, sum, subset, result);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        vector<int> subset;

        dfs(nums, target, 0, 0, subset, result);
        return result;
    }
};

// optimization: we sort the array now we only need to keep finding until target <= sum when target becomes greater than sum then all elements later would also result in sum that are greater than target which are unnecessary to search, hence return early - O(n* 2^n)
class Solution2 {
private:
    void dfs(vector<int>& nums, int target, int i, int sum, vector<int>& subset, vector<vector<int>>& result) {
        if (sum == target) {
            result.push_back(subset);
            return;
        }

        for (int j = i; j < nums.size(); j++) {
            if (sum + nums[j] > target) {
                return;
            }
            subset.push_back(nums[j]);
            dfs(nums, target, j, sum + nums[j], subset, result);
            subset.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        vector<int> subset;
        sort(nums.begin(), nums.end());
        dfs(nums, target, 0, 0, subset, result);
        
        return result;
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
