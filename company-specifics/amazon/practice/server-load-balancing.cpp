#include <bits/stdc++.h>
using namespace std;

/*
Amazon Web Services manages $N$ server bins storing compute tasks. An array items of length $N$ is given, where items[i] represents the number of active tasks assigned to the $i$-th server.In one operation, you can select the server with the maximum number of tasks (if multiple, pick any), remove 1 task from it, and reassign it to the server with the minimum number of tasks (if multiple, pick any).Return the minimum number of operations required to balance the cluster such that the difference between the maximum and minimum tasks across all servers is at most 1 (i.e., $\max(\text{items}) - \min(\text{items}) \le 1$).Constraints$1 \le N \le 10^5$$1 \le \text{items}[i] \le 10^9$Sample Test CasesExample 1:PlaintextInput: items = [1, 4, 1]
Output: 2
Explanation:Operation 1: Move 1 task from items[1] to items[0] $\rightarrow$ [2, 3, 1]Operation 2: Move 1 task from items[1] to items[2] $\rightarrow$ [2, 2, 2]Max - Min difference is $2 - 2 = 0 \le 1$. Total operations = 2.Example 2:PlaintextInput: items = [5, 5, 5]
Output: 0
Explanation:Max - Min difference is $5 - 5 = 0 \le 1$, so 0 operations are required.
*/

// so the sum before and after operations remains the same. Means we just want to make almost each element exactly same. if total sum is S and n elements then that equal base value B = [S/n] and but its not always possible to make all equal remaining elements R = S mod n would get the value B + 1. Now reducing the operations :- we sort the array and hence the elements that are larger can get the larger values B + 1 since they would be closer to it while first n-R elements can have the value B.
long long minOperations(int n, vector<long long>& items) {
    long long total_sum = 0;
    for (long long item : items) {
        total_sum += item;
    }

    long long base = total_sum / n;
    int remainder = total_sum % n;

    sort(items.begin(), items.end());

    long long operations = 0;
    for (int i = 0; i < n; i++) {
        long long target = (i < n - remainder) ? base : base + 1;
        if (items[i] > target) {
            operations += (items[i] - target);
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
        vector<long long> items(n);
        for (long long& item : items) {
            cin >> item;
        }

        cout << minOperations(n, items) << '\n';
    }

    return 0;
}
