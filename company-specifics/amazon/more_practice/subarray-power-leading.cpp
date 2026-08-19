#include <bits/stdc++.h>
using namespace std;

/*
An Amazon Automated Sorting Facility operates $N$ conveyor belts, represented by an array generators where generators[i] represents the power level of the $i$-th belt. To ensure smooth operation, the power levels must be non-decreasing (i.e., generators[i] <= generators[i+1] for all $0 \le i < N - 1$).In one operation, an electrician can choose any contiguous subarray [L, R] and increase the power level of every belt in that subarray by 1. Return the minimum number of operations required to transform the power levels into a non-decreasing sequence.Constraints$1 \le N \le 10^5$$1 \le \text{generators}[i] \le 10^9$Sample Test CasesExample 1:PlaintextInput: generators = [3, 2, 1, 5]
Output: 2
Explanation:Operation 1: Increase subarray [1, 2] (0-indexed) by 1 $\rightarrow$ [3, 3, 2, 5]Operation 2: Increase subarray [2, 2] by 1 $\rightarrow$ [3, 3, 3, 5]Sequence is now non-decreasing in 2 operations.Example 2:PlaintextInput: generators = [1, 2, 3, 4]
Output: 0
Explanation:The array is already non-decreasing, so 0 operations are required.
*/

// when we apply operation on v[i-1] then v[i] might get affected but we take it along in the subarray so it requires less operations and so the difference remains constant
long long minOperations(int n, vector<int>& generators) {
    long long operations = 0;
    for (int i = 1; i < n; i++) {
        if (generators[i] < generators[i-1]) {
            operations += (generators[i-1] - generators[i]);
        }
    }

    return operations;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> generators(n);
        for (int& a : generators) {
            cin >> a;
        }

        cout << minOperations(n, generators) << '\n';
    }

    return 0;
}
