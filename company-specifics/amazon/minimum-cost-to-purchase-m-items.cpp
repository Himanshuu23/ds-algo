#include <bits/stdc++.h>
using namespace std;

/*
Problem StatementThere are $n$ item types available at an Amazon Go Store. Each item type $i$ (0-indexed) is characterized by two parameters: $a[i]$ and $b[i]$.You can buy multiple items of the same type. The cost to purchase the $j^{\text{th}}$ item (1-indexed) of type $i$ is calculated as:$$\text{Cost}(i, j) = a[i] + (j - 1) \times b[i]$$Find the minimum total cost to purchase exactly $m$ items in total across any combination of types.Constraints$1 \le n \le 10^5$$1 \le a[i], b[i] \le 10^5$$1 \le m \le 10^5$Sample CaseInput$n = 3$$a = [2, 1, 1]$$b = [1, 2, 3]$$m = 4$Step-by-Step Purchase BreakdownPurchase 1 ($j=1$): Buy Type 1 $\rightarrow$ Cost = $1 + (1-1) \times 2 = 1$Purchase 2 ($j=1$): Buy Type 2 $\rightarrow$ Cost = $1 + (1-1) \times 3 = 1$Purchase 3 ($j=1$): Buy Type 0 $\rightarrow$ Cost = $2 + (1-1) \times 1 = 2$Purchase 4 ($j=2$): Buy Type 0 or Type 1 $\rightarrow$ Cost = $2 + (2-1) \times 1 = 3$Output7 (Total cost: $1 + 1 + 2 + 3 = 7$)
Link :- https://leetcode.com/discuss/post/4660709/amazon-oa-recent-questions-sharing-for-t-8ze5/
*/

// greedy approach using minHeap - Since we always want the cheapest item available right now across all $n$ types, we can use a Min-Heap (Priority Queue).Algorithm Step-by-StepPush the $1^{\text{st}}$ item cost ($a[i]$) for every type $i$ into a Min-Heap.Repeat $m$ times:Pop the smallest cost item currently in the heap.Add its cost to total_cost.Push the NEXT item cost for that same type into the heap: $a[i] + j \times b[i]$.
long long getMinCost(int n, vector<int>& a, vector<int>& b, int m) {
	priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;
	for (int i = 0; i < n; i++) {
		pq.push({a[i], i, 1});
	}
	long long total_cost = 0;
	for (int i = 0; i < m; i++) {
		auto [cost, type, j] = pq.top();
		pq.pop();
		total_cost += cost;
		long long next_cost = (long long)a[type] + (long long)j * b[type];
		pq.push({next_cost, type, j + 1});
	}
	return total_cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
		int n; cin >> n;
		vector<int> a(n), b(n);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];
		int m; cin >> m;
		cout << getMinCost(n, a, b, m) << '\n';
    }

    return 0;
}
