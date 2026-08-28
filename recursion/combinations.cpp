#include <bits/stdc++.h>
using namespace std;

// using recursion + backtracking - O(C(n, k)*k) - k combinations, O(k) - for recursion stack
class Solution {
    void dfs(int n, int k, int i, vector<int>& subset, vector<vector<int>>& result) {
        if (subset.size() == k) {
            result.push_back(subset);
            return;
        }

        if ((n - i + 1) < (k - subset.size()) || i > n) { // can't form k-sized subsets anymore - not enough remaining elemens => since remaining elements for ith index are (n - i + 1) and we need to make a valid subset of k sized are (k - subset.size())
            return;
        }

        subset.push_back(i);
        dfs(n, k, i + 1, subset, result);
        subset.pop_back();
        dfs(n, k, i + 1, subset, result);
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> subset;
        vector<vector<int>> result;
        dfs(n, k, 1, subset, result);

        return result;    
    }
};

// bit manipulation (TLE) - O(n*2^n) - all subsets = all masks 0 to 2^n - 1, if k bits set in that mask - valid subset
// now n sized bits are 0 to n - 1 but the number that we want to push is bit + 1
class Solution2 {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<int> combination;
            for (int bit = 0; bit < n; bit++) {
                if (mask && (1 << bit)) {
                    combination.push_back(bit + 1);
                }
            }

            if (combination.size() == k) {
                result.push_back(combination);
            }
        }

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
