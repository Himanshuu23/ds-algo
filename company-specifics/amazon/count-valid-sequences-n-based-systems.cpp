#include <bits/stdc++.h>
using namespace std;

/*
Given two integers $M$ and $N$, find the total number of $M$-digit sequences (or numbers) that can be constructed under a positional number system where each digit can range from $1$ up to $N$, subject to the following rules:The sequence has length $M$, represented as $d_1, d_2, d_3, \dots, d_M$.The value of the first digit $d_1$ must be at least $1$.The value of any digit cannot exceed $N$ (i.e., $1 \le d_i \le N$ for all $1 \le i \le M$).For every adjacent pair of digits, the current digit must be at least twice the value of the preceding digit:$$d_i \ge 2 \times d_{i-1} \quad \text{for all } 2 \le i \le M$$Input FormatTwo space-separated integers $M$ and $N$.$M$: The total number of digits in the required sequence.$N$: The maximum allowed value for any single digit.Output FormatReturn a single integer representing the total number of valid $M$-digit sequences modulo $10^9 + 7$ (or as required by standard precision rules).ExamplesExample 1:Input: M = 3, N = 9Output: 8Explanation:The valid 3-digit sequences are:[1, 2, 4][1, 2, 5][1, 2, 6][1, 2, 7][1, 2, 8][1, 2, 9][1, 3, 6][1, 3, 7][1, 3, 8][1, 3, 9][1, 4, 8][1, 4, 9][2, 4, 8][2, 4, 9](Note: Sequences like [1, 3, 5] are invalid because $5 < 2 \times 3$).
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// using dp - dp[i][j] => valid sequences of length 'i' end last digit 'j'. i can have values from 1 to M and j can have values from 1 to N. Base Case for length = 1 i.e. i = 1, all values of j would work 1...M 
// else wise for length 'i', at current place 'j' -> possible value of previous j-1 would be <= (current value) / 2 -> range of k. Hence dp[i][j] = dp[i-1][k] (all valid k values of previous) where k ranges from 1 to (current value) / 2
// finding the sum of valid values from k = 1 to k = (current_value) / 2 we use prefix sum
// Also if we have d1, d2...dm digits d1 >= 1, d2 >= 2, d3 >= 4 ... dm >= 2^m-1, Hence 2^m-1 <= N
// for M > 20, power reaches 10^6 and also for M > 31 integer overflow - since atmost 32 bits
// O(M*N), O(M*N)
const int MOD = 1e9 + 7;
int getAllValidSequences(int M, int N) {
    if (M > 20 || (1 << (M-1)) > N) return 0;

    vector<vector<long long>> dp(M+1, vector<long long> (N+1, 0));
    
    // base case
    for (int j = 1; j <= N; j++) {
        dp[1][j] = 1;
    }

    for (int i = 2; i <= M; i++) {
        long long prefix_sum = 0;
        int prev_k = 1;

        for (int j = 1; j <= N; j++) {
            while (prev_k <= j / 2) {
                prefix_sum = (prefix_sum + dp[i-1][prev_k]) % MOD;
                prev_k++;
            }
            dp[i][j] = prefix_sum;
        }
    }

    long long total_sequences = 0;
    for (int j = 1; j <= N; j++) {
        total_sequences = (total_sequences + dp[M][j]) % MOD;
    }

    return total_sequences;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        cout << getAllValidSequences(m, n) << '\n';
    }

    return 0;
}
