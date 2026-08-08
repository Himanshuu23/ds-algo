#include<bits/stdc++.h>
using namespace std;

// same as first part just now when left and middle are equal then since middle isn't target then left isn't either so we take it out of search - in worse case O(n) though depends on input 222221 and target is 1
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1;
        while (start <= end) {
            int middle = start + (end - start) / 2;
            if (nums[middle] == target) return true;
            if (nums[start] < nums[middle]) {
                if (nums[start] <= target && target < nums[middle]) {
                    end = middle - 1;
                } else {
                    start = middle + 1;
                }
            } else if (nums[start] > nums[middle]) {
                if (nums[middle] < target && target <= nums[end]) {
                    start = middle + 1;
                } else {
                    end = middle - 1;
                }
            } else {
                start++;
            }
        }

        return false;
    }
};
