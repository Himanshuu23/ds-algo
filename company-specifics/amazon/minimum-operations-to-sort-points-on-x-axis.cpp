#include <bits/stdc++.h>
using namespace std;

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
