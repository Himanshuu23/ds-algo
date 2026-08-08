#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        // find peak element
        int start = 1, end = mountainArr.length() - 2, peak = -1; // since first and last element can't be peak
        while (start <= end) {
            int middle = start + (end - start) / 2;
            int left = mountainArr.get(middle - 1);
            int m = mountainArr.get(middle);
            int right = mountainArr.get(middle + 1);
            if (left < m && right > m) {
                start = middle + 1;
            } else if (left > m && m > right) {
                end = middle - 1;
            } else {
                peak = middle;
                break;
            }
        }

        // searching in left part -> [start of array, peak)
        start = 0, end = peak - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;
            int m = mountainArr.get(middle);
            if (m > target) {
                end = middle - 1;
            } else if (m < target) {
                start = middle + 1;
            } else {
                return middle;
            }
        }

        // searching in right part -> [peak, end of array]
        start = peak, end = mountainArr.length() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;
            int m = mountainArr.get(middle);
            if (m > target) {
                start = middle + 1;
            } else if (m < target) {
                end = middle - 1;
            } else {
                return middle;
            }
        }

        return -1;
    }
};
