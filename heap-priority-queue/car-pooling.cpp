#include <bits/stdc++.h>
using namespace std;

// brute force: sort the values by their 'from' start position - for each check all previous positions if their "to" is greater than current value's "from" means we add their passengers -> if more than capacity return false else return true - merging interval
// O(n^2), O(n)
class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        sort(trips.begin(), trips.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        for (int i = 0; i < trips.size(); i++) {
            int current = trips[i][0];
            for (int j = 0; j < i; j++) {
                if (trips[j][2] > trips[i][1]) {
                    current += trips[j][0];
                }
            }
            if (current > capacity) {
                return false;
            }
        }

        return true;
    }
};

/*
at 'to' -> add the new passengers count and to-> remove those and if at any point passengers > capacity return false else return true at the end 
O(nlogn) for sorting, O(n) for new auxillary array
*/
class Solution2 {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        int n = trips.size();
        vector<pair<int, int>> merged;
        for (int i = 0; i < n; i++) {
            merged.push_back({ trips[i][1], trips[i][0] });
            merged.push_back({ trips[i][2], -trips[i][0] });
        }

        sort(merged.begin(), merged.end());

        int passengers = 0;
        for (int i = 0; i < merged.size(); i++) {
            passengers += merged[i].second;
            if (passengers > capacity) {
                return false;
            }
        }

        return true;
    }
};

// using min heap : optimization of brute force approach - process trips in order of pickup time, we only care about the passengers that are currently in the car. If the drop time of any passenger is less than pickup time for current -> remove those passengers from the heap - also removing their count from passengers count
// O(nlogn), O(n)
class Solution3 {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        sort(trips.begin(), trips.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap; // { end, number_of_passengers }
        int current = 0;
        for (auto& trip : trips) {
            int number_of_passengers = trip[0], start = trip[1], end = trip[2];

            while (!minHeap.empty() && minHeap.top().first <= start) {
                current -= minHeap.top().second;
                minHeap.pop();
            }

            current += number_of_passengers;
            if (current > capacity) {
                return false;
            }

            minHeap.push({ end, number_of_passengers });
        }

        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
