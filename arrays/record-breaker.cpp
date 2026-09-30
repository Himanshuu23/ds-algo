#include <bits/stdc++.h>
using namespace std;

// brute force: O(n^2), O(1) - for each 'i' comparing all previous indices whether they're small and also if i is not last element then also check if next element is also smaller than current element
int bruteForceApproach(vector<int>& v) {
    int n = v.size();
    int days = 0;
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = 0; j < i; j++) {
            if (v[j] >= v[i]) {
                flag = false;
                break;
            }
        }
        if (i < n - 1 && v[i] <= v[i+1]) {
            flag = false;
        }
        if (flag) ++days;
    }
    return days;
}

// optimal: O(n), O(1) - removing the inner loop by tracking just the max element of the previous elements
int solve(vector<int>& v) {
    int n = v.size(), days = 0;
    int mx = INT_MIN;
    for (int i = 0; i < n; i++) {
        bool flag = true;
        if (v[i] <= mx) flag = false;
        if (i < n - 1 && v[i] <= v[i+1]) flag = false;
        if (flag) ++days;
        mx = max(mx, v[i]);
    }
    return days;
}

int main() {
    return 0;
}
