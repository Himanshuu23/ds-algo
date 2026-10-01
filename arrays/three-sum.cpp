#include<bits/stdc++.h>
using namespace std;

// O(n^3), O(n^2)
vector<vector<int>> bruteForce(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 2; i++) { // since next loop starts from i + 1
        if (i > 0 && nums[i] == nums[i-1]) continue; // skipping duplicates
        for (int j = i + 1; j < n - 1; j++) {
            if (j > i + 1 && nums[j] == nums[j-1]) continue; // so we don't compare and skip case nums[j] and nums[i] when j = i + 1 that is valid case
            for (int k = j + 1; k < n; k++) {
                if (k > j + 1 && nums[k] == nums[k-1]) continue;
                if (nums[i] + nums[j] + nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
    }
    return result;
}

// inner two loops can be combined using two pointers: O(n^2), O(n^2)
vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n - 2; i++) { // since l is from i + 1 (avoiding out of bound errors)
        if (i && nums[i] == nums[i-1]) continue;
        int l = i + 1, r = n - 1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) {
                result.push_back({nums[i], nums[l], nums[r]});
                l++; r--;
                while (l < r && nums[l] == nums[l-1]) l++;
                while (l < r && nums[r] == nums[r+1]) r--;
            } else if (sum > 0) r--;
            else l++;
        }
    }
    return result;
}

int main() {
    int n; cin >> n;
    vector<int> v(n);

    return 0;
}
