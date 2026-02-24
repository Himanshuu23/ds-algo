#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> solve(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> answer;
    sort(nums.begin(), nums.end());
    long long sum = 0;
    for (int i = 0; i < n-3; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;
        for (int j = i+1; j < n-2; j++) {
            if (j > i+1 && nums[j] == nums[j-1]) continue;
            int left = j+1, right = n-1;
            while (left < right) {
                sum = 1LL * nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    answer.push_back({nums[i],nums[j],nums[left],nums[right]});
                    left++; right--;
                    while (left < right && nums[left] == nums[left-1]) left++;
                    while (left < right && nums[right] == nums[right+1]) right++;
                } else if (sum > target) right--;
                else left++;
            }
        }
    }

    return answer;
}

