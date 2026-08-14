#include <bits/stdc++.h>
using namespace std;

/*
Given $N$ points on a 1D $x$-axis and $M$ boxes ($M \le N$), place all $M$ boxes onto distinct points such that the minimum distance between any two adjacent placed boxes is maximized.Input FormatAn array points of size $N$ representing the coordinates on the $x$-axis.An integer $M$ representing the number of boxes to place.Output FormatReturn a single integer representing the maximum possible value of the minimum distance between adjacent boxes.Constraints$2 \le M \le N \le 10^5$$0 \le \text{points}[i] \le 10^9$ExampleInput:N = 5, points = [1, 2, 8, 4, 9]M = 3Output: 3
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// variation of aggressive cow problem
// O(NlogN)
int placeBoxes(int N, int M, vector<int>& boxes) {
    sort(boxes.begin(), boxes.end());

    auto canPlace = [&](int distance) {
        int placed = 1, last = boxes[0];
        for (int i = 1; i < N; i++) {
            if (boxes[i] - last >= distance) {
                ++placed;
                last = boxes[i];
            }
        }

        return placed >= M;
    };

    int low = 1, high = boxes.back() - boxes[0];
    int answer = high;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (canPlace(middle)) {
            answer = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
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
        int N, M; cin >> N >> M;
        vector<int> v(N);
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }

        cout << placeBoxes(N, M, v) << '\n';
    }

    return 0;
}
