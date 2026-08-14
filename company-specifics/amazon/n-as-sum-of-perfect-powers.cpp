#include <bits/stdc++.h>
using namespace std;

/*
Given an integer $N$ ($1 \le N \le 10^5$), determine the number of distinct ways to express $N$ as the sum of perfect power terms:$$N = a_1^{n_1} + a_2^{n_2} + a_3^{n_3} + \dots + a_k^{n_k}$$ConstraintsBases: $a_i \ge 2$Exponents: $n_i \ge 2$ (Perfect Powers)Repetition: Any power term can be used multiple times (Unbounded Knapsack).Order: Order of terms does not matter (combinations, not permutations).Target $N$: $1 \le N \le 10^5$Result: Output the answer modulo $10^9 + 7$.Sample Test CasesTest Case 1Input: N = 8Output: 2Valid Representations:$8$ ($2^3$)$4 + 4$ ($2^2 + 2^2$)Test Case 2Input: N = 17Output: 2Valid Representations:$9 + 8$ ($3^2 + 2^3$)$9 + 4 + 4$ ($3^2 + 2^2 + 2^2$)
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// precompute all possible powers where base >= 2 and exp >= 2 and coin knapsack dp on those so there sum is N
const int MOD = 1e9 + 7;
const int MAXN = 100000;
vector<int> dp(MAXN + 1, 0);
void precompute() {
    set<long long> powers;
    for (long long base = 2; base*base <= MAXN; base++) {
        long long value = base * base;
        while (value <= MAXN) {
            powers.insert(value);
            if (value > MAXN / base) break; // value*base > MAXN - written in this form coz value*base might overflow
            value *= base;
        }
    }

    dp[0] = 1;
    for (long long p : powers) {
        for (int i = p; i <= MAXN; i++) {
            dp[i] = (dp[i] + dp[i-p]) % MOD;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        cout << dp[N] << '\n';
    }

    return 0;
}
