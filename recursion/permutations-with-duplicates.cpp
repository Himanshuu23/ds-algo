/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void permutations(int i, vector<int> &v) {
    if (i == v.size()) {
        for (int j = 0; j < v.size(); j++) {
            cout << v[j] << " ";
        }
        cout << endl;
        return;
    }

    unordered_set<int> used;
    for (int j = i; j < v.size(); j++) {
        if (used.count(v[j])) continue;
        used.insert(v[j]);

        swap(v[i], v[j]);
        permutations(i+1, v);
        swap(v[i], v[j]);
    }
}

// O(n*n!) time and space
class Solution {
    void dfs(vector<int>& nums, int i, vector<int>& permutation, vector<vector<int>>& result) {
        if (i == nums.size()) {
            result.push_back(permutation);
            return;
        }

        unordered_set<int> used;
        for (int j = i; j < nums.size(); j++) {
            if (used.count(nums[j])) continue;
            used.insert(nums[j]);
            swap(nums[i], nums[j]);
            permutation.push_back(nums[i]);
            dfs(nums, i + 1, permutation, result);
            swap(nums[i], nums[j]);
            permutation.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> permutation;
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());

        dfs(nums, 0, permutation, result);

        return result;
    }
};

// optimization: no need for set
class Solution3 {
    vector<vector<int>> result;

    void dfs(int i, vector<int>& nums) {
        if (i == nums.size()) {
            result.push_back(nums);
            return;
        }

        for (int j = i; j < nums.size(); ++j) {
            if (j > i && nums[j] == nums[i]) continue; // since i == j also satisfies nums[i] == nums[j] we don't want to miss that
            swap(nums[i], nums[j]);
            dfs(i + 1, nums);
        }

        // restoration loop: since we are checking nums[i] == nums[j] but after each call we are swapping nums[i] with nums[j] so nums[i] might not be same that we're expecting it to be, hence this restoration loop gets back that nums[i] that we're expecting
        for (int j = nums.size() - 1; j > i; --j) {
            swap(nums[i], nums[j]);
        }
    }

public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dfs(0, nums);
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(), v.end());
        permutations(0, v);
    }

    return 0;
}
