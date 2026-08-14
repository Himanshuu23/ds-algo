#include <bits/stdc++.h>
using namespace std;

/*
Given an array arr[] of $N$ integers, rearrange the numbers into the lexicographically next greater permutation of numbers.If such an arrangement is not possible (i.e., the array is sorted in descending order), rearrange it to the lowest possible order (i.e., sorted in ascending order).The replacement must be done in-place using only $\mathcal{O}(1)$ extra memory.Input FormatAn integer array arr of size $N$.Output FormatModify the array arr in-place to represent the next permutation.Constraints$1 \le N \le 10^5$$1 \le \text{arr}[i] \le 10^5$Expected Time Complexity: $\mathcal{O}(N)$Expected Auxiliary Space: $\mathcal{O}(1)$ExamplesExample 1Input: arr = [2, 4, 1, 7, 5, 0]Output: [2, 4, 5, 0, 1, 7]Explanation: The lexicographically next permutation after [2, 4, 1, 7, 5, 0] is [2, 4, 5, 0, 1, 7].Example 2Input: arr = [3, 2, 1]Output: [1, 2, 3]Explanation: Since [3, 2, 1] is the largest possible permutation, it wraps around to the lowest possible order.
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// we must work from right to left (least significants first). we need to find the first pivot that is right to left first element such that v[i] < v[i+1]
// then we go again from right to left and j such that v[j] > v[i] (if no such element means we're at last permutation - 3 2 1 - just reverse the string) then we swap these two, now still suffix i + 1 to end are decreasing order -> reverse that 
// O(N), O(1)
void nextPermutation(int n, vector<int>& v) {
    int i = n - 2;
    while (i >= 0 && v[i] >= v[i+1]) {
        i--;
    }
    if (i >= 0) {
        int j = n - 1;
        while (v[j] <= v[i]) {
            j--;
        }
        swap(v[i], v[j]);
    }
    reverse(v.begin() + i + 1, v.end());
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
        nextPermutation(n, v);
        for (int x : v) {
            cout << x << " ";
        }
        cout << '\n';
    }

    return 0;
}
