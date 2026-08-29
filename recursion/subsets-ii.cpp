#include<bits/stdc++.h>
using namespace std;

// brute force - dfs finding all subset but set won't let insert duplicates - O(n*2^n), O(2^n) for recursion stack
class Solution {
private:
    void dfs(const vector<int>& nums, int i, vector<int>& subset, set<vector<int>>& result) {
        if (i == nums.size()) {
            result.insert(subset);
            return;
        }

        subset.push_back(nums[i]);
        dfs(nums, i + 1, subset, result);
        subset.pop_back();
        dfs(nums, i + 1, subset, result);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        set<vector<int>> result;
        vector<int> subset;
        dfs(nums, 0, subset, result);
        return vector<vector<int>>(result.begin(), result.end());
    }
};

// optimization: duplicates are only created - when while going through each element we have two choices (take it, don't take it) when don't take it and next element is also the same -> duplicates are created. So we skip those and don't process all subsets at all
class Solution2 {
private:
    void dfs(const vector<int>& nums, int i, vector<int>& subset, set<vector<int>>& result) {
        if (i >= nums.size()) {
            result.insert(subset);
            return;
        }

        subset.push_back(nums[i]);
        dfs(nums, i + 1, subset, result);
        subset.pop_back();
        while (i + 1 < nums.size() && nums[i] == nums[i+1]) i++;
        dfs(nums, i + 1, subset, result);
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        set<vector<int>> result;
        vector<int> subset;
        dfs(nums, 0, subset, result);
        return vector<vector<int>>(result.begin(), result.end());
    }
};
