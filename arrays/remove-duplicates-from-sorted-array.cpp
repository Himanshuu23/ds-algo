#include<bits/stdc++.h>
using namespace std;

// O(n), O(1)
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

// O(n), O(1)
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

// O(n), O(1)
class Solution {
    public:
        int removeDuplicates(vector<int>& v) {
            int n = v.size();
            if (n == 0) return 0;
            int w = 1; // last written element
            for (int i = 1; i < n; i++) {
                if (v[i] != v[w-1]) v[w++] = v[i]; // if previously written element not equal to the current element 
            }
            return w;
        }
};
