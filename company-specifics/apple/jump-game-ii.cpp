#include<bits/stdc++.h>
using namespace std;

/*
Problem Statement
Given a 0-indexed array of integers nums of length n, where each element represents your maximum jump length, return the minimum number of jumps required to reach nums[n - 1].
Approach: O(n), O(1)
treat each jump as exploring a level or range of reachable indices (like BFS). Instead of making a decision at every single step. you can scall all reachable indices in your current jump window to find the absolute furthest point you can reach in your next jump.
(i) track boundaries: currentEnd - marks the furthest boundary you can reach with your current number of jumps. farthest - tracks the absolute maximum reach you can prepare for next jump.
(ii) scan the window as we iterate: at each index i update farthest = max(farthest, nums[i] + i)
(iii) commit the jump when we reach currentEnd, it means we have explored all choices for current jump. committing new jump -> jump++ so update currentEnd = farthest
(iv) exit early - if currentEnd reaches or passes final index (n - 1) break immediately
*/

int jump(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;

    int jumps = 0;
    int currentEnd = 0;
    int farthest = 0;
    
    for (int i = 0; i < n - 1; i++) { // not checking last index coz that is the destination only
        farthest = max(farthest, nums[i] + i);

        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;

            if (currentEnd >= n - 1) return jumps;
        }
    }

    return jumps;
}
