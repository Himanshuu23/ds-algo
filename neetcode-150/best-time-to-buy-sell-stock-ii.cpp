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
