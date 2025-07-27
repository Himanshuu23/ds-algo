/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double solve(vector<int>& nums1, vector<int>& nums2) {
    int m(nums1.size()), n(nums2.size());
    if (m > n) return solve(nums2, nums1);

    int l(0), r(m);

    while (l <= r) {
        int partitionX = (l + r) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
        int maxRightY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];

        if (maxLeftX <= minRightY && maxRightY <= minRightX) {
            if ((m + n) % 2 == 0) return (max(maxLeftX, maxRightY) + min(minRightX, minRightY)) / 2.0;
            else return max(maxLeftX, maxRightY);
        } else if (maxLeftX > minRightY) r = partitionX - 1;
        else l = partitionX + 1;
    }

    return -1.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
