#include <bits/stdc++.h>
using namespace std;

// using recursion - O(2^n), O(n)
class Solution {
private:
    int dfs(vector<int>& cost, int i) {
        if (i >= cost.size()) {
            return 0;
        }

        return cost[i] + min(dfs(cost, i + 1), dfs(cost, i + 2));
    }
public:
    int minCostClimbingStairs(vector<int>& cost) {
        return min(dfs(cost, 0), dfs(cost, 1)); // starting from 0th stair or 1st stair - taking the answer that is minimum
    }
};

// top - down dp: O(n), O(n) - caching/memoizing previous solution since many calculation repeat
class Solution2 {
private:
    vector<int> cache;
    int dfs(vector<int>& cost, int i) {
        if (i >= cost.size()) {
            return 0;
        }
        if (cache[i] != -1) return cache[i];

        return cache[i] = cost[i] + min(dfs(cost, i + 1), dfs(cost, i + 2));
    }
public:
    int minCostClimbingStairs(vector<int>& cost) {
        cache.assign(cost.size() + 1, -1);

        return min(dfs(cost, 0), dfs(cost, 1));
    }
};

// bottom up dp: O(n), O(n)
class Solution3 {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n + 1, 0);
        
        // initializing dp[0] = 0, and dp[1] covers the part where we can start either from 0 or 1st step
        for (int i = 2; i <= n; i++) {
            dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2]);
        }

        return dp[n];
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
