#include <bits/stdc++.h>
using namespace std;

/*
There are $n$ points on an X-axis. The $i^{\text{th}}$ point initially resides at position $i$ (0-indexed) and has a weight weight[i] and a step size dist[i].In a single operation, you can move the $i^{\text{th}}$ point to the right by its step distance (position[i] = position[i] + dist[i]).Find the minimum total operations required so that the final positions of the points are strictly increasing when ordered by their weights (i.e., a point with a smaller weight must end up at a strictly smaller X-position than a point with a larger weight).Sample CasesSample Case 1Input: weight = [3, 6, 5, 2], dist = [4, 3, 2, 1]Output: 5Sample Case 2Input: weight = [2, 4, 3, 1], dist = [2, 6, 3, 5]Output: 4
Link : https://leetcode.com/discuss/post/6225872/amazon-oa-questions-2025-sde2-by-anonymo-qrs8/
*/

// greedy - place the smallest weight first - coz after placing it we don't have to care about it just next elements
// O(nlogn + total_operations), O(n)
int brute_force(int n, vector<int>& weights, vector<int>& distances) {
	vector<tuple<int, int, int>> points(n);
	for (int i = 0; i < n; i++) {
		points[i] = { weights[i], distances[i], i };
	}
	sort(points.begin(), points.end());
	int answer = 0;
	long long last_position = -1;
	for (int i = 0; i < n; i++) {
		auto [w, d, original_position] = points[i];
		long long current_position = original_position;

		while (current_position <= last_position) {
			++answer;
			current_position += d;
		}

		last_position = current_position;
	}

	return answer;
}

// optimization of above solution -> instead of while loop, required position would be last position + 1 so we can directly find that in O(1) using formula :-
// moves = max(0, required position - current position) / d -> ceil division since round down can go to current position only
// O(nlogn), O(n)
long long minimum_operations(int n, vector<int>& weights, vector<int>& distances) {
	vector<tuple<int, int, int>> points(n);
	for (int i = 0; i < n; i++) {
		points[i] = { weights[i], distances[i], i };
	}
	sort(points.begin(), points.end());
	long long answer = 0;
	long long last_position = -1;
	for (int i = 0; i < n; i++) {
		auto [w, d, original_position] = points[i];
		long long current_position = original_position;
		if (current_position <= last_position) {
			long long required_position = (last_position + 1) - current_position;
			long long moves = (required_position + d - 1) / d;
			current_position += moves * d;
			answer += moves;
		}
		last_position = current_position;
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
		vector<int> weights(n), distances(n);
		for (int i = 0; i < n; i++) cin >> weights[i];
		for (int i = 0; i < n; i++) cin >> distances[i];
		cout << brute_force(n, weights, distances) << '\n';
		cout << minimum_operations(n, weights, distances) << '\n';
    }

    return 0;
}
