#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve(int i, vector<int>& nums, vector<vector<int>>& answer) {
        if (i == nums.size()) {
            answer.push_back(nums);
            return;
        }

        for (int j = i; j < nums.size(); j++) {
            swap(nums[j], nums[i]);
            solve(i+1, nums, answer);
            swap(nums[j], nums[i]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> answer;

        solve(0, nums, answer);

        return answer;
    }
};
