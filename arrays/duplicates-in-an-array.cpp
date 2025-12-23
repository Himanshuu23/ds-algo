#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            int index = abs(nums[i])-1;
            if (nums[index] < 0) result.push_back(index+1);
            else nums[index] *= -1;
        }

        return result;
    }
};
