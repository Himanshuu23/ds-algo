#include<bits/stdc++.h>
using namespace std;

// Floyd Cycle Detection: since the elements are within [1, n] -> so we make graph with each node value = v[i] and children pointing to the index at value v[i] i.e. v[v[i]]. The element which leads to cycle is the duplicate element. O(n), O(1)
// first when slow and fast pointers meet they will be inside the cycle, now resetting and moving again will make them meet at the start of the cycle.
// formula derivation: suppose x is the distance from the start of the cycle to first element, c is the length of the cycle and y is the distance of where they meet during first phase to the entrance of the cycle. Now distance travelled by fast = 2x slow
// distance travelled by slow = x + (c - y)
// distance travelled by fast = x + k*c + (c - y) - suppose it did 'k' movements inside the cycle as well
// now x + k*c + (c - y) = 2x + 2(c - y) => x = y + (k - 1) -> means the distance between the entrance of the cycle to the start position index 0 and point where they meet is same. means when we reset the fast to start it would meet slow at the entrance of the cycle.
int solve(vector<int>& v) {
    int slow = 0, fast = 0;
    do {
        slow = v[slow];
        fast = v[v[fast]];
    } while (slow != fast);
    fast = 0;
    while (fast != slow) {
        fast = v[fast];
        slow = v[slow];
    }
    return slow;
}

int main() {

	return 0;
} 
