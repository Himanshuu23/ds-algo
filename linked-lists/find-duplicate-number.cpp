#include <bits/stdc++.h>
using namespace std;

// brute force -> O(N), O(N)
class Solution2 {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_set<int> s;
        for (int x : nums) {
            if (s.count(x) == 0) s.insert(x);
            else return x;
        }
        return -1;
    }

};

// using floyd algorithm
// if the distance from start of linked list and start of cycle is P, distance between start of the cycle and intersection point is X then remaining part of the cycle is C - X where C is length of the cycle.
// Now first time when fast and slow pointers meet then fast must have travelled P + nC - X (as many cycles till slow reaches and they meet) and slow would have travelled P + C - X distance 
// Now 2 * slow = fast => 2 (P + C - X) = P + nC - X => (taking n = 2) => C = X
// means if we reset the fast pointer and move it one way and slow pointer moves from where the met earlier towards start then both the distance are same and they meet exactly at the start of the cycle which is the required result
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow(0), fast(0), n = nums.size();
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }

        fast = 0;
        while (true) {
            slow = nums[slow];
            fast = nums[fast];
            if (slow == fast) return slow;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
