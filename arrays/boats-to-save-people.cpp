#include<bits/stdc++.h>
using namespace std;

// Brute force: take the first unused person i. Either send them alone (n-1 people remain)
// or pair with any unused j that fits (n-2 remain), then recurse and take the min.
// Pairing-only chain is (n-1)(n-3)...1 = (n-1)!!; the "alone" branches add more paths,
// so the true count is larger (about sqrt(n!)), but still exponential.
// So pairing only is n!! but alone creates more branches so slightly higher than n!!. Not n! since that is way slower.
// Worst case: everyone can pair with everyone (most branching).
// The number of ways to pick disjoint pairs from n people (leftovers alone) is called the telephone number T(n). It follows a known recurrence:
// T(n) = T(n-1) + (n-1) * T(n-2) - T(n-1): person i goes alone, n - 1 people remain. (n-1) * T(n-2): person i pairs with one of n - 1 partners, n - 2 people remain. √(n!) is the complexity for this.
// Space: O(n) for recursion stack + used[].
int solve(vector<int>& people, int limit, vector<bool>& used) {
    int i = 0;
    while (i < people.size() && used[i]) i++; // continue the loop if already paired this person
    if (i == people.size()) return 0;
    used[i] = true;
    int best = 1 + solve(people, limit, used); // sending alone
    for (int j = i + 1; j < people.size(); j++) {
        if (!used[j] && people[i] + people[j] <= limit) {
            used[j] = true;
            best = min(best, 1 + solve(people, limit, used)); // trying to pair
            used[j] = false;
        }
    }
    used[i] = false;
    return best;
}

// O(nlogn), O(1)
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size(), left = 0, right = n - 1;
		sort(people.begin(), people.end());
		int answer = 0;
		while (left <= right) {
			if (people[left] + people[right] <= limit) {
				left++; right--;
			} else {
				right--;
			}
			++answer;
		}

		return answer;
	}
};
