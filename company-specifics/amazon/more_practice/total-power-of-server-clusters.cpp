#include <bits/stdc++.h>
using namespace std;

/*
Amazon operates a sequence of $n$ servers placed in a row. The $i$-th server has a processing power given by power[i].A cluster is defined as any non-empty contiguous subarray of servers. The total strength of a cluster is defined as the product of:The minimum processing power among all servers in that cluster.The sum of processing powers of all servers in that cluster.Return the sum of the total strengths of all possible contiguous server clusters. Since the answer can be very large, return it modulo $10^9 + 7$.Input Formatpower: An array of $n$ positive integers representing the power of each server.Output FormatReturn a single integer: the sum of total strengths for all contiguous clusters modulo $10^9 + 7$.Constraints$1 \le n \le 10^5$$1 \le \text{power}[i] \le 10^9$Example 1Input:power = [2, 1, 3]Output: 47Explanation:The contiguous clusters and their total strengths are:[2] $\rightarrow \min=2, \text{sum}=2 \implies 2 \times 2 = 4$[1] $\rightarrow \min=1, \text{sum}=1 \implies 1 \times 1 = 1$[3] $\rightarrow \min=3, \text{sum}=3 \implies 3 \times 3 = 9$[2, 1] $\rightarrow \min=1, \text{sum}=3 \implies 1 \times 3 = 3$[1, 3] $\rightarrow \min=1, \text{sum}=4 \implies 1 \times 4 = 4$[2, 1, 3] $\rightarrow \min=1, \text{sum}=6 \implies 1 \times 6 = 6$Total Strength Sum $= 4 + 1 + 9 + 3 + 4 + 6 = 27$(Wait, let's sum them: $4+1+9+3+4+6 = 27$.)Corrected Output: 27Example 2Input:power = [1, 2]Output: 9Explanation:[1] $\rightarrow 1 \times 1 = 1$[2] $\rightarrow 2 \times 2 = 4$[1, 2] $\rightarrow 1 \times 3 = 3$Total $= 1 + 4 + 3 = 8$(Wait, $1 + 4 + 3 = 8$.)Corrected Output: 8
*/

/*
 * APPROACH: Monotonic Stack + Prefix of Prefix Sums (PP)
 * 1. Contribution Technique: Treat powers[i] as the minimum element for all subarrays 
 *    in range [L, R]. Find boundaries L and R using Monotonic Stacks in O(N). -> finding till what window size v[i] is min element hence we can find its contribution 
 *    - Use '>=' on one side and '>' on the other to prevent double-counting duplicate minimums. -> element itself
 * 
 * 2. Subarray Sum Math: Sum of subarray [l, r] is (P[r+1] - P[l]), where P is Prefix Sum.
 *    Over all (l, r) pairs: Total Sum = (right_part * left_count) - (left_part * right_count)
 *    - left_count  = (i - L + 1)
 *    - right_count = (R - i + 1)
 * 
 * 3. Range Sum Optimization (PP Array):
 *    - Right Part: Sum of P[i+1 ... R+1]  ==>  PP[R+2] - PP[i+1] -> (sum upto R + 1) - (sum upto i)
 *    - Left Part : Sum of P[L ... i]      ==>  PP[i+1] - PP[L] -> (sum upto i) - (sum upto L - 1) -> since we wanna include P[L] from prefix sum in prefix sum of prefix sum
 *right_part = sum of positive prefix terms ($P[r+1]$) $\rightarrow$ multiplied by how many starting points $l$ exist (left_count).left_part = sum of negative prefix terms ($P[l]$) $\rightarrow$ multiplied by how many ending points $r$ exist (right_count).
 also right part includes the subarray where powers[i] is alone while left doesn't so we dont recount it
 
 4. Final Answer: Add (powers[i] * Total Sum) % MOD for each element i.
 */
// O(N)
const int MOD = 1e9 + 7;
long long solve(int n, vector<int>& powers) {
    vector<long long> P(n+1, 0), PP(n+2, 0);
    for (int i = 0; i < n; i++) {
        P[i+1] = (P[i] + powers[i]) % MOD;
    }
    for (int i = 0; i <= n; i++) {
        PP[i+1] = (PP[i] + P[i]) % MOD;
    }

    vector<int> left(n, -1), right(n, n);
    stack<int> st;

    for (int i = 0; i < n; i++) {
        while (!st.empty() && powers[st.top()] >= powers[i]) st.pop();
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && powers[st.top()] > powers[i]) st.pop();
        if (!st.empty()) right[i] = st.top();
        st.push(i);
    }

    long long answer = 0;
    for (int i = 0; i < n; i++) {
        int L = left[i] + 1, R = right[i] - 1;

        long long left_part = (PP[i+1] - PP[L] + MOD) % MOD;
        long long right_part = (PP[R+2] - PP[i+1] + MOD) % MOD;

        long long left_count = i - L + 1;
        long long right_count = R - i + 1;

        long long total_subarray_sum = (right_part * left_count % MOD - left_part * right_count % MOD + MOD) % MOD;
        answer = (answer + total_subarray_sum * powers[i]) % MOD;
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        cout << solve(n, v) << '\n';
    }

    return 0;
}
