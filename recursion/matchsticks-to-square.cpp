#include<bits/stdc++.h>
using namespace std;

// using backtracking - just dividing total sum into 4 equal sums - O(4^n), O(n)
class Solution {
private:
    bool dfs(vector<int>& matchsticks, vector<int>& sides, int i) {
        if (i == matchsticks.size()) {
            return sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3];
        }

        for (int j = 0; j < 4; j++) {
            sides[j] += matchsticks[i];
            if (dfs(matchsticks, sides, i + 1)) {
                return true;
            }

            sides[j] -= matchsticks[i];
        }

        return false;
    }
public:
    bool makesquare(vector<int>& matchsticks) {
        long long sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);

        if (sum % 4) {
            return false;
        }

        vector<int> sides(4, 0);
        
        return dfs(matchsticks, sides, 0);
    }
};

// two optimizations (Pruning) to approach above : (i) sort the sticks in the descending order so we fail early - like suppose checking for sum = 10, we try 1, 2 but then we don't have 7 so we tried 2 sticks earlier but descending order we try larger ones early and sum goes above 10 early. (ii) if we already tried an empty side and couldn't place on it then donot try another empty side since both are same things - just repititon.
// time complexities are same as above, above solution TLEs but this works
class Solution2 {
private:
    bool dfs(vector<int>& matchsticks, vector<int>& sides, int i, int length) {
        if (i == matchsticks.size()) {
            return true;
        }

        for (int j = 0; j < 4; j++) {
            if (sides[j] + matchsticks[i] <= length) {
                sides[j] += matchsticks[i];
                if (dfs(matchsticks, sides, i + 1, length)) {
                    return true;
                }

                sides[j] -= matchsticks[i];
            }

            if (sides[j] == 0) break; // above we're tring empty + non empty sides where this matchstick can be placed - if that doesn't works out then another empty side wouldn't work either
        }

        return false;
    }
public:
    bool makesquare(vector<int>& matchsticks) {
        long long totalLength = accumulate(matchsticks.begin(), matchsticks.end(), 0);

        if (totalLength % 4) {
            return false;
        }

        int length = totalLength / 4;
        vector<int> sides(4, 0);
        sort(matchsticks.rbegin(), matchsticks.rend());
        
        return dfs(matchsticks, sides, 0, length);
    }
};

// trying every subset and if current bit is set means we haven't used that matchstick yet. Also reusing the result for each subset using dp so not precomputing that again - each subset only once. We can only use that matchstick to make the current side if including it doesn't goes beyond the length limit.
// O(n * 2^n), O(n + 2^n) - since for each matchstick either we its already used or available so 2^n * n, space complexity is 2*n for subsets and n for recursion stack
class Solution3 {
private:
    vector<int> dp;
    int length, n;

    int dfs(int mask, vector<int>& matchsticks) {
        if (mask == 0) return 0; // no matchstick available
        if (dp[mask] != INT_MIN) return dp[mask];

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) { // bit is set -> means matchstick is available
                int result = dfs(mask ^ (1 << i), matchsticks); // using that bit (setting to zero)
                if (result >= 0 && result + matchsticks[i] <= length) { // using this matchstick doesn't exceeds the length
                    dp[mask] = (result + matchsticks[i]) % length;
                    return dp[mask]; // returns current length that we've built
                }

                if (mask == (1 << n) - 1) { // cannot use this matchstick in this current side
                    dp[mask] = -1;
                    return -1;
                }
            }
        }

        dp[mask] = -1; // could not use this matchstick anywhere - on any side
        return dp[mask];
    }
public:
    bool makesquare(vector<int>& matchsticks) {
        int totalLength = accumulate(matchsticks.begin(), matchsticks.end(), 0);

        if (totalLength % 4 != 0) return false;

        length = totalLength / 4;
        if (*max_element(matchsticks.begin(), matchsticks.end()) > length) {
            return false;
        }

        sort(matchsticks.rbegin(), matchsticks.rend());
        n = matchsticks.size();
        dp.resize(1 << n, INT_MIN);

        return dfs((1 << n) - 1, matchsticks) == 0; // all bits/matchsticks have been used
    }
};
