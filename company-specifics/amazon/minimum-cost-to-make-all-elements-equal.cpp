#include <bits/stdc++.h>
using namespace std;

/*
You are given an array arr of length $n$ representing the display values at each Amazon fulfillment station positioned in a line from left to right.You can perform two types of operations any number of times (possibly zero):Left Propagation: Choose an index $i$ ($1 \le i \le n - 1$) and set all prefix positions $0, 1, \dots, i - 1$ to $\text{arr}[i]$.Cost: $i \times \text{arr}[i]$Right Propagation: Choose an index $i$ ($0 \le i \le n - 2$) and set all suffix positions $i + 1, i + 2, \dots, n - 1$ to $\text{arr}[i]$.Cost: $(n - 1 - i) \times \text{arr}[i]$Compute the minimum total cost required to make all array elements equal.Input FormatAn integer $n$, the length of the array.An integer array arr of size $n$.Output FormatReturn a single integer representing the minimum total cost to make all elements equal.ExampleInput:n = 4arr = [3, 1, 4, 2]Output: 3Explanation:Choose $i = 1$ ($\text{arr}[1] = 1$) for Left Propagation:Set position $0$ to $1$.Cost = $1 \times \text{arr}[1] = 1 \times 1 = 1$.Array becomes: [1, 1, 4, 2].Choose $i = 1$ ($\text{arr}[1] = 1$) for Right Propagation:Set positions $2$ and $3$ to $1$.Cost = $(4 - 1 - 1) \times \text{arr}[1] = 2 \times 1 = 2$.Array becomes: [1, 1, 1, 1].Total Minimum Cost = $1 + 2 = 3$.
*/

// total cost of v[i] = prefix cost + suffix cost = (i * v[i]) + (n - 1 - i) * v[i] = (i + n - 1 - i) * v[i] = (n - 1) * v[i]
// hence cost dependent on just v[i] -> just find min element of array
// O(N), O(1)
long long minCost(int n, vector<int>& v) {
    int min_element = INT_MAX;
    for (int i = 0; i < n; i++) {
        min_element = min(min_element, v[i]);
    }

    return 1LL * (n - 1) * min_element;
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
        cout << minCost(n, v) << '\n';
    }

    return 0;
}
