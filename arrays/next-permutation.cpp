#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void reverse(vector<int>& v, int start) {
    int l = start, r = v.size()-1;
    while (l < r) {
        swap(v[l], v[r]);
        l++; r--;
    }
}

void solve(vector<int> nums) {
    int n = nums.size(), idx1 = -1, idx2 = -1;
    for (int i = n-2; i >= 0; i--) {
        if (nums[i] < nums[i+1]) {
            idx1 = i;
            break;
        }
    }

    if (idx1 == -1) reverse(nums, 0);
    else {
        for (int i = n-1; i >= 0; i--) {
            if (nums[i] > nums[idx1]) {
                idx2 = i;
                break;
            }
        }
        
        swap(nums[idx1], nums[idx2]);
        reverse(nums, idx1+1);
    }
}
