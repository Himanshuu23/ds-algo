#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> solve(vector<int>& nums) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<vector<int>> answer;
    int sum = 0;
    for (int i = 0; i < n-2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        int l = i+1, r = n-1;
        while (l < r) {
            sum = nums[l] + nums[r] + nums[i];
            if (sum == 0) {
                answer.push_back({nums[l], nums[r], nums[i]});
                l++; r--;
                while (l < r && nums[l] == nums[l-1]) l++;
                while (l < r && nums[r] == nums[r+1]) r--;
            }
            else if (sum > 0) r--;
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
