/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// brute force: traverse each element and put each number at each place in already permutations we have. O(n^2*n!), O(n*n!)
// new number = 3 and if we already permutations = { {1, 2}, {2, 1} } -> { {3,1,2}, { 1,3,2}, {1, 2, 3}, {3, 2, 1}, {2, 3, 1}, {2, 1, 3}}
// we have to initialize result by empty array since that is also initially part of permutation building
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result = {{}};
        for (int num : nums) {
            vector<vector<int>> new_permutation;
            for (const auto& p : result) {
                for (int i = 0; i <= p.size(); i++) {
                    vector<int> copy = p;
                    copy.insert(copy.begin() + i, num);
                    new_permutation.push_back(copy);
                }
            }
            result = new_permutation;
        }

        return result;
    }
};

// O(n*n!) space and time since there n! permutations and for each, we do result.push_back() which copies O(n)
class Solution2 {
private:
    void permutation(vector<int>& nums, int i, vector<int>& v, vector<vector<int>>& result) {
        if (i == nums.size()) {
            result.push_back(v);
            return;
        }

        for (int j = i; j < nums.size(); j++) {
            swap(nums[i], nums[j]);
            v.push_back(nums[i]);
            permutation(nums, i + 1, v, result);
            swap(nums[i], nums[j]);
            v.pop_back();
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> v;
        vector<vector<int>> result;
        permutation(nums, 0, v, result);

        return result;
    }
};

void permutations(ll i, vector<int> &v) {
    if (i == v.size()) { 
        for (int j = 0; j < v.size(); j++) { 
            cout << v[j] << " "; 
        }
        cout << endl;
        return;
    }
    for (int j = i; j < v.size(); j++) {
        swap(v[j], v[i]);
        permutations(i+1, v);
        swap(v[j], v[i]);
    }
}

// bit manipulation + backtracking - O(n*n!) - time and space. for each ith index we set the ith bit means nums[i] -> all set bits are used in the current permutation -> the ones not checked -> we backtrack and recurse.
// mask = 101 means indices 0 and 2 are used. nums[0] that is 1 and nums[2] that is 3 are used.
// at each level -> n indices -> we have n! choices => n × (n-1) × (n-2) × ... × 1 = n! and copying a permutation (pushing into result) takes O(n)
class Solution3 {
private:
    void backtrack(vector<int>& nums, int mask, vector<int>& permutation, vector<vector<int>>& result) {
        if (permutation.size() == nums.size()) {
            result.push_back(permutation);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (!(mask & (1 << i))) { // if the current bit isn't used
                permutation.push_back(nums[i]); // push that element
                backtrack(nums, mask | (1 << i), permutation, result); // setting that bit 
                permutation.pop_back(); // backtrack
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> permutation;
        backtrack(nums, 0, permutation, result);

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
        permutations(0, v);
    }

    return 0;
}
