#include <bits/stdc++.h>
using namespace std;

// recursion + backtracking - skipping duplicates so we generate only unique subsets. Also sorting early so if at some point while traversing 'i' value we have adding this element > target means we can't include that element in our current subset and all other elements after it can't be either so we return early instead of exploring them
// O(n* 2^n)
class Solution {
private:
    void dfs(const vector<int>& nums, int target, int i, int sum, vector<int>& subset, vector<vector<int>>& result) {
        if (sum == target) {
            result.push_back(subset);
            return;
        }

        for (int j = i; j < nums.size(); j++) {
            if (j > i && nums[j] == nums[j-1]) continue;
            if (sum + nums[j] > target) {
                return;
            }

            subset.push_back(nums[j]);
            dfs(nums, target, j + 1, sum + nums[j], subset, result);
            subset.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<int> subset;
        vector<vector<int>> result;
        dfs(candidates, target, 0, 0, subset, result);
        
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
