#include <bits/stdc++.h>
using namespace std;

/*
An array data contains $n$ integers (1-indexed). A permutation $p$ of length $n$ contains all integers from $1$ to $n$.The information gained for a permutation $p$ is calculated as:$$\text{Gain} = \sum_{i=1}^{n} i \times \text{data}[p[i]]$$Find the lexicographically smallest permutation $p$ that maximizes the total information gained.Constraints$1 \le n \le 10^5$$1 \le \text{data}[i] \le 10^9$Sample CaseInput: n = 3, data = [2, 1, 2]Evaluated Permutations:$p = [2, 1, 3] \rightarrow 1 \times \text{data}[2] + 2 \times \text{data}[1] + 3 \times \text{data}[3] = 1(1) + 2(2) + 3(2) = \mathbf{11}$$p = [2, 3, 1] \rightarrow 1 \times \text{data}[2] + 2 \times \text{data}[3] + 3 \times \text{data}[1] = 1(1) + 2(2) + 3(2) = \mathbf{11}$Output: [2, 1, 3] (Since both give max gain $11$, but [2, 1, 3] is lexicographically smaller than [2, 3, 1])
https://leetcode.com/discuss/post/6438689/amazon-oa-question-sde-ii-by-anonymous_u-ujke/
*/

// brute force - try all permutations and return the one with max gain + lexicographically smaller - O(N*N!), O(N)
vector<int> brute_force(int n, vector<int>& data) {
	vector<int> p(n), answer(n);
	iota(p.begin(), p.end(), 1);
	long long gain = -1;
	do {
		long long current_gain = 0;
		for (int i = 0; i < n; i++) {
			current_gain += (long long)(i + 1) * data[p[i]-1];
		}
		if (current_gain > gain) {
			gain = current_gain;
			answer = p;
		}
	} while (next_permutation(p.begin(), p.end()));

	return answer;
}

// greedy -> values with higher data values must be present at high indices to maximize the gain but if gain are same then we want to place smaller indices first
// to get the lexicographically smallest condition
vector<int> greedy(int n, vector<int>& data) {
	vector<pair<int, int>> pairs(n);
	for (int i = 0; i < n; i++) {
		pairs[i] = {data[i], i+1};
	}

	sort(pairs.begin(), pairs.end());
	vector<int> p(n);
	for (int i = 0; i < n; i++) {
		p[i] = pairs[i].second;
	}

	return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
		int n; cin >> n;
		vector<int> data(n);
		for (int i = 0; i < n; i++) cin >> data[i];
		vector<int> answer1(n), answer2(n);
		answer1 = brute_force(n, data);
		answer2 = greedy(n, data);
		for (int x : answer1) cout << x << " ";
		cout << '\n';
		for (int x : answer2) cout << x << " ";
		cout << '\n';
    }

    return 0;
}
