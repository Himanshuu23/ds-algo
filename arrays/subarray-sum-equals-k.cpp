#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        int prefix = 0, n = nums.size(), answer(0);
        map[0] = 1;

        for (int i = 0; i < n; i++) {
            prefix += nums[i];
            answer += map[prefix-k];
            map[prefix]++;
        }

        return answer;
    }
};
