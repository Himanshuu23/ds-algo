#include <bits/stdc++.h>
using namespace std;

/*
There is a linear chain of $n$ servers represented by an array cost of size $n$, where cost[i] is the cost parameter associated with the $i^{\text{th}}$ server.You need to partition the servers sequentially into exactly $k$ contiguous, non-empty server chains (subarrays) such that every element belongs to exactly one partition.Cost FormulaThe cost of a single server chain starting at index $i$ and ending at index $j$ is defined as:$$\text{Chain Cost} = \text{cost}[i] + \text{cost}[j]$$The total cost is the sum of the costs of all $k$ server chains.TaskFind both the minimum and maximum possible total cost to partition the $n$ servers into $k$ chains.Return the result as an array of size 2:$$\text{Output} = [\text{minimum cost}, \text{maximum cost}]$$ExampleInput: cost = [1, 2, 3, 2, 5], k = 3Possible Partitions:[1], [2], [3, 2, 5] $\rightarrow (1+1) + (2+2) + (3+5) = 2 + 4 + 8 = 14$[1, 2, 3], [2], [5] $\rightarrow (1+3) + (2+2) + (5+5) = 4 + 4 + 10 = 18$Minimum Cost: 14Maximum Cost: 18Output: [14, 18]Function SignatureC++vector<int> findPartitionCost(vector<int> cost, int k)
Link - https://www.reddit.com/r/leetcode/comments/1j96wui/amazon_oa_question/
*/

// cost[0] and cost[n-1] are always added to the cost
// now each split creates a boundary -> hence for a split at i, we add cost[i], cost[i+1]
// hence we just have to find pair sum -> and try each split -> each pair sum take k-1 max, min since for k partitions - k splits are required and always add base = cost[0] + cost[n-1]
// O(nlogn), O(n) using sorting
vector<long long> findPartitionCost(vector<int>& cost, int k) {
    int n = cost.size();
    long long min_cost = (long long)cost[0] + cost[n-1], max_cost = (long long)cost[0] + cost[n-1];
    vector<long long> pairs;
    for (int i = 0; i < n - 1; i++) {
        pairs.push_back((long long)cost[i] + cost[i+1]);
    }

    sort(pairs.begin(), pairs.end());
    for (int i = 0; i < k - 1; i++) {
        min_cost += pairs[i]; 
    }

    for (int i = n - 2; i >= n - k; i--) {
        max_cost += pairs[i];
    }

    return { min_cost, max_cost };
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<int> cost(n);
        for (int i = 0; i < n; i++) {
            cin >> cost[i];
        }

        vector<long long> answer = findPartitionCost(cost, k);
        cout << answer[0] << " " << answer[1] << '\n';
    }

    return 0;
}
