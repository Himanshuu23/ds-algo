#include<bits/stdc++.h>
using namespace std;

// Brute Force
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int answer = *max_element(weights.begin(), weights.end());
        while (true) {
            int d = 0, capacity = 0, placed = 0;
            for (int w : weights) {
                if (w > answer) break;
                if (w + capacity <= answer) {
                    capacity += w;
                    ++placed;
                } else {
                    ++d;
                    capacity = w;
                    ++placed;
                }
            }
            ++d;
            if (d <= days && placed == weights.size()) break;
            else {
                answer++;
                d = 0;
                capacity = 0;
                placed = 0;
            }
        }

        return answer;
    }
};

// Binary Search - n(logn)
class Solution1 {
public:
    bool canShip(vector<int>& weights, int days, int capacity) {
        int placed = 0, current = 0, day = 0;
        for (int i = 0; i < weights.size(); i++) {
            if (weights[i] > capacity) break;
            if (weights[i] + current <= capacity) {
                current += weights[i];
                ++placed;
            } else {
                ++day;
                current = weights[i];
                ++placed;
            }
        }
        ++day;

        return placed == weights.size() && day <= days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int start = *max_element(weights.begin(), weights.end());
        int end = accumulate(weights.begin(), weights.end(), 0);
        int answer = end;
        while (start <= end) {
            int middle = (start + end) / 2;
            if (canShip(weights, days, middle)) {
                answer = middle;
                end = middle - 1;
            } else start = middle + 1;
        }

        return answer;
    }
};
