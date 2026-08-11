#include <bits/stdc++.h>
using namespace std;

/*
Amazon Web Services has $n$ servers, where the $i^{\text{th}}$ server has a power rating of power[i].The cache optimization power of a contiguous subarray of servers $[l, r]$ (where $0 \le l \le r < n$) is defined as:$$\text{Power}[l, r] = \left( \min_{l \le i \le r} \text{power}[i] \right) \times \left( \sum_{i=l}^{r} \text{power}[i] \right)$$TaskFind the sum of $\text{Power}[l, r]$ for all possible contiguous groups of servers. Since the total sum can be very large, return the result modulo $10^9 + 7$.Constraints$1 \le n \le 8 \times 10^5$$1 \le \text{power}[i] \le 10^9$Sample CasesSample Case 0Input: power = [2, 1, 3]Output: 27Explanation:$\text{Power}[0, 0] = \min([2]) \times \text{sum}([2]) = 2 \times 2 = 4$$\text{Power}[0, 1] = \min([2, 1]) \times \text{sum}([2, 1]) = 1 \times 3 = 3$$\text{Power}[0, 2] = \min([2, 1, 3]) \times \text{sum}([2, 1, 3]) = 1 \times 6 = 6$$\text{Power}[1, 1] = \min([1]) \times \text{sum}([1]) = 1 \times 1 = 1$$\text{Power}[1, 2] = \min([1, 3]) \times \text{sum}([1, 3]) = 1 \times 4 = 4$$\text{Power}[2, 2] = \min([3]) \times \text{sum}([3]) = 3 \times 3 = 9$Total Sum: $4 + 3 + 6 + 1 + 4 + 9 = 27$Sample Case 1Input: power = [2, 4]Output: 32Explanation:$\text{Power}[0, 0] = 2 \times 2 = 4$$\text{Power}[0, 1] = 2 \times 6 = 12$$\text{Power}[1, 1] = 4 \times 4 = 16$Total Sum: $4 + 12 + 16 = 32$
Link - https://leetcode.com/discuss/post/1737071/amazon-oa-sde-90-min-by-anonymous_user-w7gp/
Similar Problem - LeetCode 2281: Sum of Total Strength of Wizards
*/

// Brute force : go to each n*(n+1)/2 subarrays -> O(n^2)
// Using a Monotonic Stack, for every index $i$, find:$L$: The nearest index to the left with a smaller element (power[L] < power[i]).$R$: The nearest index to the right with a smaller or equal element (power[R] <= power[i]).Meaning: power[i] is the minimum for any subarray starting at $l \in [L+1, i]$ and ending at $r \in [i, R-1]$.
//For fixed $i$, we need:$$\sum_{l=L+1}^{i} \sum_{r=i}^{R-1} \text{Sum}(l, r)$$Since $\text{Sum}(l, r) = P[r+1] - P[l]$ (where $P$ is the standard Prefix Sum array), expanding the double sum gives:$$\left( (i - L) \cdot \sum_{r=i}^{R-1} P[r+1] \right) - \left( (R - i) \cdot \sum_{l=L+1}^{i} P[l] \right). Prefix Sum of Prefix Sums ($PP$)To compute range sums of $P$ in $\mathcal{O}(1)$ time, create a Prefix Sum of Prefix Sums array:$$PP[x] = \sum_{j=0}^{x} P[j]$$Now:$\sum_{r=i}^{R-1} P[r+1] = PP[R] - PP[i]$$\sum_{l=L+1}^{i} P[l] = PP[i] - PP[L]$
// more on prefix sum of prefix sum -> PP - v[i] -> element at ith index, P[i] = sum of v[0] till v[i], pp[i] = sum of p[0]...p[i]
// now when we find suppose sum[0,2] = p[3] - p[0], sum[1,2] = p[3] - p[1], sum[2,2] = p[3] - p[2] -> adding all these together requires p[0] + p[1] + p[2] -> which prefix of prefix sum gives in O(1) -> pp[2] = p[0] + p[1] + p[2]
// left -> we're checking strictly smaller elements while right we're checking less than or equal to - allowing us not to double count like [2,3,2] both 2 are min for whole array so we would eventually double count but using strictly less or left we get : first 2 -> -1 on left and right has 2 -> [2,3], while second 2 -> left is index 0 -> [3,2] while right is -1 -> [2,3,2]
//O(N), O(N)
long long solve(int n, vector<int>& power) {
    long long MOD = 1e9 + 7;
    
    // building prefix sum (1 based) not 0 based coz then prefix sum is p[r]-p[l-1] hence for first element l-1 is negative so we require extra check but here just p[r+1]-p[l]
    vector<long long> P(n+1, 0);
    for (int i = 0; i < n; i++) {
        P[i+1] = (P[i] + power[i]) % MOD;
    }

    vector<long long> PP(n+2, 0);
    for (int i = 0; i <= n; i++) {
        PP[i+1] = (PP[i] + P[i]) % MOD;
    }

    vector<int> left_bound(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && power[st.top()] >= power[i]) {
            st.pop();
        }
        if (!st.empty()) left_bound[i] = st.top();
        st.push(i);
    }

    vector<int> right_bound(n, n);
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && power[st.top()] > power[i]) {
            st.pop();
        }
        if (!st.empty()) right_bound[i] = st.top();
        st.push(i);
    }

    long long total_power = 0;
    for (int i = 0; i < n; i++) {
        int L = left_bound[i];
        int R = right_bound[i];

        long long left_count = i - L;
        long long right_count = R - i;
        
        // since to find sum of subarrays in (0, i) using pp[i] we do pp[i] just that but since lower bound and upper bound array store 0 based indexing wew would have done pp[i+1] and so we're using the same for [l, r] range pp[r+1] - pp[l+1]
        long long right_sum = (PP[R+1] - PP[i+1] + MOD) % MOD;
        long long left_sum = (PP[i+1] - PP[L+1] + MOD) % MOD;

        long long subarray_sum = (right_sum * left_count % MOD - left_sum * right_count % MOD + MOD) % MOD;
        
        long long contribution = (subarray_sum * power[i]) % MOD;
        total_power = (total_power + contribution) % MOD;
    }

    return total_power;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> power(n);
        for (int i = 0; i < n; i++) {
            cin >> power[i];
        }
        
        cout << solve(n, power) << '\n';
    }

    return 0;
}
