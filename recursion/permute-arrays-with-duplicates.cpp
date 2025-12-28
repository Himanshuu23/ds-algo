#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve(int i, vector<int>& nums, vector<vector<int>>& answer) {
        if (i == nums.size()) {
            answer.push_back(nums);
            return;
        }

        unordered_set<int> used;
        for (int j = i; j < nums.size(); j++) {
            if (used.count(nums[j])) continue;
            
            used.insert(nums[j]);
            swap(nums[i], nums[j]);
            solve(i+1, nums, answer);
            swap(nums[i], nums[j]);
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> answer;
        solve(0, nums, answer);
        return answer;
    }
};
