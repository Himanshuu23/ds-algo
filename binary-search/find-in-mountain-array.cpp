#include<bits/stdc++.h>
using namespace std;

// without cache solution is O(logn), O(1) but to do less API calls and improving performance we use cache to not retrieve same values again from API - O(logn), O(logn)
class Solution {
    unordered_map<int, int> cache;

    int get(int index, MountainArray & mountainArr) {
        if (cache.find(index) == cache.end()) {
            cache[index] = mountainArr.get(index);
        }
        return cache[index];
    }

public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        // find peak element
        int start = 1, end = mountainArr.length() - 2, peak = -1; // since first and last element can't be peak
        while (start <= end) {
            int middle = start + (end - start) / 2;
            int left = get(middle - 1, mountainArr);
            int m = get(middle, mountainArr);
            int right = get(middle + 1, mountainArr);
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
            int m = get(middle, mountainArr);
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
            int m = get(middle, mountainArr);
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
