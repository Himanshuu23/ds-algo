class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> answer(nums.size());
        answer[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) answer[i] = nums[i] + answer[i-1];
        return answer;
    }
};
