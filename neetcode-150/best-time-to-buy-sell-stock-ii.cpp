class Solution {
public:
int solve(int i, int bought, vector<int>& v, vector<vector<int>>& dp) {
	if (i >= v.size()) return 0;
	if (dp[i][bought] != -1) return dp[i][bought];
	int answer = solve(i+1, bought, v, dp);
	if (bought) {
		answer = max(answer, v[i] + solve(i+1, 0, v, dp));
	} else {
		answer = max(answer, solve(i+1, 1, v, dp) - v[i]);
	}
	return dp[i][bought] = answer;
}

    int maxProfit(vector<int>& v) {
        int n = v.size();
        vector<vector<int>> dp(n, vector<int> (2, -1));
		return solve(0, 0, v, dp);
    }
};

// bottom up 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int i = n - 1; i >= 0; i--) {
            dp[i][0] = max(dp[i + 1][0], -prices[i] + dp[i + 1][1]);
            dp[i][1] = max(dp[i + 1][1], prices[i] + dp[i + 1][0]);
        }

        return dp[0][0];
    }
};

// optimized bottom up - only next [i-1] required for current so O(1) space
int solve(vector<int>& v) {
	int nextBuy = 0, nextSell = 0;
	int currentBuy = 0, currentSell = 0;
	
	for (int i = v.size() - 1; i >= 0; i--) {
		currentBuy = max(currentBuy, nextSell - v[i]);
		currentSell = max(currentSell, v[i] + nextBuy);
		nextBuy = currentBuy;
		nextSell = currentSell;
	}

	return currentBuy;
}
