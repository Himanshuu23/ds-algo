#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
		int n = nums.size(), l = 0, r = 0;
		while (r < n) {
			nums[l] = nums[r];
			while (r < n && nums[l] == nums[r]) r++;
			l++;
		}
		return l;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int w(0), r(0), prev(-1e3);

        while (r < nums.size()) {
            int curr = nums[r];
            if (curr != prev) {
                prev = curr;
                nums[w] = curr;
                w++;
            }
            r++;
        }

        return w;
    }
};
