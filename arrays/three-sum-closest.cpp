#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int>& nums, int target) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int sum = 0, answer = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < n-2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        int l = i+1, r = n-1;
        while (l < r) {
            sum = nums[l] + nums[r] + nums[i];
            if (abs(target - sum) < abs(target - answer)) {
                answer = sum;
                l++; r--;
                while (l < r && nums[l] == nums[l-1]) l++;
                while (l < r && nums[r] == nums[r+1]) r--;
            }
            else if (target > sum) r--;
            else l++;
        }
    }

    return answer;
}


int main() {
    int n; cin >> n;
    vector<int> v(n);

    return 0;
}
