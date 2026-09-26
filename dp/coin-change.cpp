/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// recursive: O(n^t), O(t) where n are the total number of coins and t is the amount
class Solution {
private:
    int dfs(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        int answer = INT_MAX;
        for (int coin : coins) {
            if (amount - coin >= 0) {
                answer = min(answer, 1 + dfs(coins, amount - coin));
            }
        }
        return answer;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int minCoins = dfs(coins, amount);
        return (minCoins == INT_MAX ? -1 : minCoins);
    }
};

// top down dp: O(n * t), O(t)
class Solution2 {
private:
    unordered_map<int, int> cache;
    int dfs(vector<int>& coins, int amount) {
        if (amount == 0) return 0;
        if (cache.find(amount) != cache.end()) {
            return cache[amount];
        }

        int answer = INT_MAX;
        for (int coin : coins) {
            if (amount - coin >= 0) {
                int result = dfs(coins, amount - coin); // to avoid 1 + INT_MAX = INT_MIN
                if (result != INT_MAX) {
                    answer = min(answer, 1 + result);
                }
            }
        }

        cache[amount] = answer;
        return answer;
    }
public:
    int coinChange(vector<int>& coins, int amount) {
        int minCoins = dfs(coins, amount);
        return (minCoins == INT_MAX ? -1 : minCoins);
    }
};

// bottom up dp: O(n*t), O(t)
class Solution3 {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }
        return (dp[amount] > amount ? -1 : dp[amount]);
    }
};

// using bfs: O(n * t), O(t)
// each node is a amount, from which we can go to coin + amount with each edge costing '1', now we have to find shortest path from 0 to amount - bfs is perfect fit
class Solution4 {
public:
    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) return 0;

        queue<int> q;
        q.push(0);
        vector<bool> seen(amount + 1, false);
        seen[0] = true;
        int answer = 0;

        while (!q.empty()) {
            ++answer;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                int current = q.front();
                q.pop();
                for (int coin : coins) {
                    int next = current + coin;
                    if (next == amount) return answer;
                    if (next > amount || seen[next]) continue;
                    seen[next] = true;
                    q.push(next);
                }
            }
        }

        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, amt; cin >> n >> amt;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        vector<int> dp(amt+1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amt; i++) {
            for (int x : v) {
                if (i-x>=0 && dp[i-x] != INT_MAX) dp[i] = min(dp[i], dp[i-x]+1);
            }
        }
        cout << (dp[amt] == INT_MAX ? -1 : dp[amt]) << endl;
    }

    return 0;
}
