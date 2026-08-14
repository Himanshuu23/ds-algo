#include <bits/stdc++.h>
using namespace std;

/*
Consider a game where a player can score 3, 5, or 10 points in a single move. Given a total target score $N$, find the total number of distinct combinations of moves to reach exact score $N$.(Note: Order does not matter. For example, $3 + 5$ and $5 + 3$ are considered the same combination).Input Formatn: An integer representing the target score ($N \ge 0$).Output FormatReturn a long integer representing the total number of distinct combinations to reach score $N$.ExamplesExample 1:Input: n = 20Output: 4Explanation: The 4 distinct combinations are:10 + 1010 + 5 + 55 + 5 + 5 + 55 + 3 + 3 + 3 + 3 + 3Example 2:Input: n = 13Output: 2Explanation: The 2 distinct combinations are:10 + 35 + 5 + 3Example 3:Input: n = 8Output: 1Explanation: Only 1 valid combination: 5 + 3.
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// coin change dp
long long numberOfWays(int N) {
    vector<long long> dp(N+1, 0);
    dp[0] = 1;
    int points[] = { 3, 5, 10 };
    for (int p : points) {
        for (int i = p; i <= N; i++) {
            dp[i] += dp[i-p];
        }
    }

    return dp[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << numberOfWays(n) << '\n';
    }

    return 0;
}
