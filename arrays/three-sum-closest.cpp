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
    sum = nums[i] + nums[l] + nums[r];

    if (sum == target) return target;

    if (abs(target - sum) < abs(target - answer))
        answer = sum;

    if (sum > target) r--;
    else l++;
}    }

    return answer;
}


int main() {
    int n; cin >> n;
    vector<int> v(n);

    return 0;
}
