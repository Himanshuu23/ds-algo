#include <bits/stdc++.h>
using namespace std;

/*
*Amazon logistics needs to transport $N$ main packages (with sizes given in an integer array packages) using at most $K$ delivery trucks. Main packages must be loaded in contiguous sequence without changing their order. Additionally, there are $M$ extra unsorted packages of size 1 that can be freely assigned to any truck. Find the minimum integer truck capacity $C$ such that all $N$ main packages and $M$ extra packages fit into at most $K$ trucks.Constraints$1 \le N \le 10^5$$1 \le \text{packages}[i] \le 10^4$$1 \le K \le 10^5$$0 \le M \le 10^9$/
Example 1:
Plaintext
Input: packages = [2, 3, 4, 1, 5], K = 3, M = 2
Output: 6
Explanation:
Truck 1: Main packages [2, 3] (sum 5) + 1 extra package = 6
Truck 2: Main packages [4, 1] (sum 5) + 1 extra package = 6
Truck 3: Main package [5] (sum 5) = 5
Result: All packages delivered in 3 trucks with maximum truck load 6.

Example 2:
Plaintext
Input: packages = [7, 2, 5, 10, 8], K = 2, M = 6
Output: 19
Explanation:
Truck 1: Main packages [7, 2, 5] (sum 14) + 5 extra packages = 19
Truck 2: Main packages [10, 8] (sum 18) + 1 extra package = 19
Result: Total volume is 38 across 2 trucks, requiring a minimum capacity of 19.
*/

// O(nlog(sum_of_capacities + m)) -> just binary search for minimum capacity
bool canFitK(int n, int m, int k, long long C, vector<long long>& capacity) {
    long long sum = 0;
    long long total_sum = 0;
    int trucks = 1;

    for (long long c : capacity) {
        if (c > C) return false;
        total_sum += c;
        if (sum + c <= C) {
            sum += c;
        } else {
            trucks++;
            sum = c;
        }
    }

    return trucks <= k && (1LL * k * C >= total_sum + m);
}

long long findMaximumCapacity(int n, int m, int k, vector<long long>& capacity) {
    long long answer = 0; 
    long long total_sum = 0, max_package = INT_MIN;
    for (long long c : capacity) {
        total_sum += c;
        max_package = max(max_package, c);
    }
    long long low = max(max_package, (total_sum + m + k - 1) / k), high = total_sum + m;
    while (low <= high) {
        long long C = low + (high - low) / 2;
        if (canFitK(n, m, k, C, capacity)) {
            answer = C;
            high = C - 1;
        } else {
            low = C + 1;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<long long> capacity(n);
        for (long long &c : capacity) {
            cin >> c;
        }

        cout << findMaximumCapacity(n, m, k, capacity) << '\n';
    }

    return 0;
}
