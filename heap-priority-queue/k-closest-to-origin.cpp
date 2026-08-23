/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// using sorting - O(nlogn), O(1) - no auxiallary space
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        sort(points.begin(), points.end(), [](const auto& a, const auto& b) {
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
        });

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;

        // maxHeap - O(nlogk), O(k)
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>> pq; 
        for (int i = 0; i < n; i++) {
            int p1, p2;
            cin >> p1; cin >> p2;
            long long distance = (p1 * p1) + (p2 * p2);
            pq.push({ distance, p1, p2 });
            if (pq.size() > k) pq.pop();
        }
        while (!pq.empty()) {
            auto [dist, x, y] = pq.top();
            pq.pop();
            cout << "(" << x << ", " << y << ") ";
        }
        cout << endl;
    }

    return 0;
}
