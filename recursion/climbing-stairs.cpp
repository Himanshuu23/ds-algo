#include<bits/stdc++.h>
using namespace std;

class Solution { // O(2^n) solution
public:
    void solve(int start, int end, int& answer) {
        if (start > end) return;
        if (start == end) ++answer;
        for (int i = 1; i <= 2; i++) solve(start+i, end, answer);
    }

    int climbStairs(int n) {
        int count = 0;
        solve(0, n, count);
        return count;
    }
};

// dp - O(n)
int solve(int i, vector<int>& dp) {
    if (i < 0) return 0;
    if (i == 0 || i == 1) return 1;
    if (dp[i] != -1) return dp[i];
    return dp[i] = solve(i-1, dp) + solve(i-2, dp);
}
