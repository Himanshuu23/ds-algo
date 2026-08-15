#include <bits/stdc++.h>
using namespace std;

/*
Amazon Web Services (AWS) is processing a stream of $n$ system log metrics represented by an array metrics.You need to partition the entire array into the maximum number of non-empty contiguous subsegments such that every subsegment has a sum of metrics strictly greater than zero ($> 0$).Return the maximum number of valid contiguous subsegments you can partition the array into. If it is impossible to partition the entire array such that every subsegment sum is strictly positive, return -1.Input Formatmetrics: An array of $n$ integers representing the log metric values.Output FormatReturn a single integer representing the maximum number of valid partitions, or -1 if no valid partitioning exists.Constraints$1 \le n \le 10^5$$-10^9 \le \text{metrics}[i] \le 10^9$Example 1Input:metrics = [2, -1, 3, -4, 5]Output: 3Explanation:We can partition the array into $3$ valid contiguous subsegments:[2] (sum = $2 > 0$)[-1, 3] (sum = $2 > 0$)[-4, 5] (sum = $1 > 0$)Total valid partitions = 3.Example 2Input:metrics = [-2, 1, 2, -1]Output: 2Explanation:We can partition the array into $2$ valid subsegments:[-2, 1, 2] (sum = $1 > 0$)[-1] has sum $-1 \le 0$ (invalid).Instead, partition as:[-2, 1, 2, -1] (sum = $0$, invalid)Or: [-2, 1] (sum = $-1$, invalid).Wait! Can we do [-2, 1, 2] (sum = 1) and we need all elements covered. Is [-2, 1, 2, -1] (sum = 0)? No.What about [-2, 1, 2] and no elements left? That leaves -1.Let's check if metrics = [-2, 3, -1, 2] works:[-2, 3] (sum = 1)[-1, 2] (sum = 1)Total = 2 partitions.Example 3Input:metrics = [-1, -2, -3]Output: -1Explanation:Every non-empty contiguous subsegment has a negative sum, so no valid partition exists.
*/

class FenwickTree {
    public:
    int size;
    vector<int> tree;

    FenwickTree(int n) : size(n), tree(n + 1, -1e9) {}

    // maintaining max DP value at each compressed sum rank
    void update(int index, int value) {
        for (; index <= size; index += (index & -index)) {
            tree[index] = max(tree[index], value);
        }
    }

    // query max DP value overall sum ranks strictly smaller than index
    int query(int index) {
        int result = -1e9;
        for (; index > 0; index -= (index & -index)) {
            result = max(result, tree[index]);
        }
        return result;
    }
};

/*
 O(NlogN), O(N)
 1. Subsegment Condition: Segment sum from (j+1 to i) is > 0 if P[j] < P[i] (where P is prefix sum).
 2. DP State: DP[i] = max valid partitions for array prefix ending at index i.
    Transition: DP[i] = 1 + max(DP[j]) for all previous j where P[j] < P[i].
 3. Coordinate Compression: Map negative/large prefix sums to 1-based sorted ranks (1 to M).
 4. Fenwick Tree (BIT): Stores the maximum DP score achieved at each prefix sum rank.
    - query(rank - 1): Finds max DP among all strictly smaller prefix sums in O(log N).
    - update(rank, DP[i]): Stores current DP score at prefix sum rank in O(log N).
 */
int partitionServerLogs(int n, vector<int>& v) {
    vector<long long> prefix_sum(n + 1, 0);
    set<long long> s;
    s.insert(0);

    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + v[i];
        s.insert(prefix_sum[i+1]);
    }

    vector<long long> all_sums(s.begin(), s.end());
    sort(all_sums.begin(), all_sums.end());

    auto getRank = [&](long long value) {
        return lower_bound(all_sums.begin(), all_sums.end(), value) - all_sums.begin() + 1;   
    };

    FenwickTree ft(all_sums.size());
    ft.update(getRank(0), 0);

    int current_dp = -1;
    for (int i = 1; i <= n; i++) {
        current_dp = -1;
        int rank = getRank(prefix_sum[i]); 
        int best_previous = ft.query(rank - 1);
        if (best_previous > -1e8) {
            current_dp = best_previous + 1;
            ft.update(rank, current_dp);
        }
    }

    return current_dp <= 0 ? -1 : current_dp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int& x : v) {
            cin >> x;
        }

        cout << partitionServerLogs(n, v) << '\n';
    }

    return 0;
}
