#include <bits/stdc++.h>
using namespace std;

// using recursion + backtracking - O(n*2^n)
class Solution {
private:
    void dfs(const vector<int>& nums, int i, vector<int>& subset, vector<vector<int>>& result) {
        if (i == nums.size()) {
            result.push_back(subset);
            return;
        }
        subset.push_back(nums[i]);
        dfs(nums, i + 1, subset, result);
        subset.pop_back();
        dfs(nums, i + 1, subset, result);
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> subset;
        dfs(nums, 0, subset, result);
        return result;
    }
};

// iterative - for each element, currently to all the subsets that we have add this element
class Solution2 {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result = {{}};
        
        for (int num : nums) {
            int size = result.size();
            for (int i = 0; i < size; i++) {
                vector<int> subset = result[i];
                subset.push_back(num);
                result.push_back(subset);
            }
        }

        return result;
    }
};

// using bit masking - O(n*2^n) - checking for each mask and bit is set include that element
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int mask = (1 << n);
        vector<vector<int>> subsets;
        for (int i = 0; i < mask; i++) {
            vector<int> subset;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    subset.push_back(nums[j]);
                }
            }
            subsets.push_back(subset);
        }
        return subsets;
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
