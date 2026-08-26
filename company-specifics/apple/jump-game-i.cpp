#include<bits/stdc++.h>
using namespace std;

/*
Problem Statement
Given an integer array nums, you start at the first index. Each element represents your maximum jump length at that position. Return true if you can reach the last index, or false otherwise.
Approach:
Track the maximum index you can reach (maxReach).
Iterate through the array index by index.
If you ever reach an index i that is greater than maxReach, it means you've hit a "dead end" zero and cannot proceed further — return false.
Otherwise, update maxReach to max(maxReach, i + nums[i]).
If maxReach reaches or exceeds the last index, return true.
maxReach -> maximum stamina - furthes index we can currently walk to. As we walk, we extend the stamina using the jump value at current spot => nums[i] + i
(i) check for dead ends: if i > maxReach means we have walked past our max stamina limit - we can't do anything stuck return false
(ii) updating max point we can go to
(iii) if in between we find we can reach then its guranteed to reach n - 1 return true early
O(n), O(1)
*/

bool canJump(vector<int>& nums) {
    int maxReach = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        if (i > maxReach) { // can't reach here
            return false;
        }

        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= n - 1) {
            return true;
        }
    }

    return true;
}
