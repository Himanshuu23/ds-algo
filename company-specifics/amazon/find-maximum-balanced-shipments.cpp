#include <bits/stdc++.h>
using namespace std;

/* 
Problem StatementAmazon has multiple delivery centers for the distribution of its goods. In one such center, parcels are arranged in a sequence where the $i^{\text{th}}$ parcel has a weight of weight[i]. A shipment is constituted of a contiguous segment of parcels in this arrangement.These shipments are to be loaded for delivery and must be balanced.A shipment is said to be balanced if the weight of the last parcel of the shipment is not the maximum weight among all the weights in that shipment.Example of a balanced shipment:[3, 9, 4, 7] is balanced because the last weight is $7$, while the maximum weight in the shipment is $9$ ($7 \neq 9$).Example of an unbalanced shipment:[4, 7, 2, 7] is not balanced because the last weight is $7$, which is also the maximum weight in the shipment.Given the weights of $n$ parcels placed in a sequence, find the maximum number of balanced shipments that can be formed such that:Each parcel belongs to exactly one shipment.Each shipment consists of only a contiguous segment of parcels.Every shipment is balanced.If there are no valid partitions, return 0.Function DescriptionComplete the function findMaximumBalancedShipments in the editor.Parameters:int weight[n]: An array of integers representing the weights of the parcels.Returns:int: The maximum possible number of balanced shipments that can be formed.Constraints$2 \le n \le 10^5$$1 \le \text{weight}[i] \le 10^9$Sample Test CasesSample Case 0Input: weight = [8, 5, 4, 7, 2]Output: 2Explanation:We can form 2 balanced shipments as [[8, 5], [4, 7, 2]] or [[8, 5, 4], [7, 2]]. In both valid partitions, the maximum number of shipments formed is 2.Sample Case 1Input: weight = [4, 3, 6, 5, 3, 4, 7, 1]Output: 3Explanation:We can partition the parcels into 3 balanced shipments: [[4, 3, 6, 5], [3, 4, 7, 1]], [[4, 3], [6, 5], [3, 4, 7, 1]], or [[4, 3, 6, 5, 3], [4, 7, 1]]. It is not possible to form more than 3 balanced shipments.
Link: https://leetcode.com/discuss/post/4846016/amazon-oa-by-anonymous_user-cfeu/
*/

// brute force - 2D DP - O(n^2), O(n)
int brute_force(int n, vector<int>& v) {
	vector<int> dp(n, -1);
	for (int i = 0; i < n; i++) {
		int mx = v[i];
		for (int j = i; j >= 0; j--) {
			mx = max(mx, v[j]);
			if (v[i] < mx) {
				if (j == 0) { // if (0...i) is balanced then this form one complete shipment
					dp[i] = max(dp[i], 1);
				} else if (dp[j-1] != -1) { // means in (0...i) we have multiple shipments since dp[j-1] is not -1 -> it formed shipments too
					dp[i] = max(dp[i], 1 + dp[j-1]);
				}	
			}
		}	
	}

	return (dp[n-1] == -1 ? 0 : dp[n-1]);
}

// Using DP + Monotonic Stack - O(n), O(n)
/*
For a shipment weight[j ... i-1] to be balanced, the last element weight[i-1] must not be the maximum of that segment.This condition holds if and only if there is at least one element in weight[j ... i-1] that is strictly greater than weight[i-1].If k is the nearest index to the left where weight[k] > weight[i-1], then any starting index $j \le k$ will include weight[k], guaranteeing a valid shipment! To maximize $dp[j]$, we simply need the maximum $dp$ value among all indices $\le k$. Since prefix maximums of $dp$ are non-decreasing, $\max(dp[0 \dots k]) = \text{pref\_max}[k]$.
*/
int optimized(int n, vector<int>& v) {
	vector<int> dp(n+1, -1), prefix_max(n+1, 0);
	stack<int> st;
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		int current_weight = v[i-1];
		while (!st.empty() && v[st.top()] <= current_weight) {
			st.pop();
		}

		if (!st.empty()) {
			int k = st.top();
			if (prefix_max[k] >= 0 || k == 0) {
				dp[i] = 1 + prefix_max[k];
			}
		}

		prefix_max[i] = max(prefix_max[i-1], dp[i]);
		st.push(i-1);
	}

	return (dp[n] == -1 ? 0 : dp[n]);
}

// Using Greedy - O(n), O(1)
int greedy(int n, vector<int>& v) {
	int answer = 0, i = 0, last_start = -1;
	while (i < n) {
		long long mx = v[i];
		int j = i + 1;
		bool found = false;
		while (j < n) {
			if (v[j] < mx) {
				answer++;
				last_start = i;
				i = j + 1;
				found = true;
				break;
			}
			mx = max(mx, (long long)v[j]);
			j++;
		}

		// handling leftovers
		if (!found) {
			if (answer == 0) return 0;
			long long full_max = INT_MIN;
			for (int k = last_start; k < n; k++) {
				full_max = max(full_max, (long long)v[k]);
			}

			if (v[n-1] >= full_max) return 0;
			break;
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
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << greedy(n, v) << '\n';
		cout << brute_force(n, v) << '\n';
    }

    return 0;
}
