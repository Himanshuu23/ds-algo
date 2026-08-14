#include <bits/stdc++.h>
using namespace std;

/*
Given an array arr[] of $N$ elements, write a function to randomly shuffle the array in-place. The shuffling must be unbiased, meaning every possible permutation of the array must be equally likely to occur (probability $\frac{1}{N!}$).Input FormatAn array arr of size $N$.Output FormatThe array modified in-place representing a uniform random permutation.Constraints$1 \le N \le 10^5$Expected Time Complexity: $\mathcal{O}(N)$Expected Auxiliary Space: $\mathcal{O}(1)$ (In-place)ExampleInput:arr = [1, 2, 3, 4, 5, 6]Output:[4, 1, 6, 2, 5, 3] (or any of the $6! = 720$ valid random permutations with equal probability)
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// fisher yates shuffle/algorithm - picking a random index from 0 to i (the remaining unplaced range) instead of picking across the entire array (0 to N - 1) every time.
// 0 to i avoids bais coz - naive way (rand() % N everytime) this generate N^N total outcomes since N^N is not divisibly by N!(for N > 2) - since it contains some prime numbers like N - 1, for eg: N = 3, we have 3^3=27 but 27/6 = 4.5 we can't divide. some permutations will inevitably occur more frequently than others. Fisher Yates : (rand() % (i+1)) - choices made at each step are N x (N - 1) x (N - 2) ... 1 = N! total outcomes. Each permutation gets exactly 1/N! probability.
// O(N), O(1)
// analogy: suppose we have row of cards faced up on a table. start at last index (i = n-1) -> roll a die to pick any card from unshuffled portion [0, i] say position j. swap card[i] with card[j]. Now slot i is locked and done. Move one step -> i = i - 1 and repeat for remaining cards. Hence, every card gets equal chance to be swapped into a locked position - so every final arrangement is equally likely.

void shuffleArray(vector<int>& v) {
    int n = v.size();
    // Mersenne Twister RNG - high quality random number generator engine
    mt19937 rng(random_device{}());
    for (int i = n - 1; i > 0; i--) {
        // pick a random index j in range [0, i]
        uniform_int_distribution<int> dist(0, i); // die that rolls between 0 to i only
        int j = dist(rng); // rolling the die to get the random index j
        swap(v[i], v[j]); // swapping the current last unshuffled element i with picked element j
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int& x : v) {
            cin >> x;
        }
        shuffleArray(v);
        for (int x : v) {
            cout << x << " ";
        }
        cout << '\n';
    }

    return 0;
}
