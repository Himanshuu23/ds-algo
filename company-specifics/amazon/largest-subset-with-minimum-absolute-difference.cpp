#include <bits/stdc++.h>
using namespace std;

/*
Given an array of integers arr and a non-negative integer y, find the maximum size of a subset such that the absolute difference between any two elements in the subset is at least y:$$\forall a, b \in \text{subset} \quad (a \neq b) \implies \vert{}a - b\vert{} \ge y$$Input Formatarr: A vector/array of $N$ integers.y: An integer representing the minimum required difference between any two chosen elements.Output FormatReturn an integer representing the maximum number of elements in a valid subset.ExampleInput:arr = [-900, 1, 1, 2, 100, 101, 2, 4, 5, 10, 18, 20, 15]y = 4Output:7Explanation:After sorting arr: [-900, 1, 1, 2, 2, 4, 5, 10, 15, 18, 20, 100, 101]One largest valid subset is {-900, 1, 5, 10, 15, 20, 100}, where every pair has an absolute difference $\ge 4$.
Link - https://leetcode.com/discuss/post/5931693/amazon-sde-6m-internship-interview-exper-qy1a/
*/

// sort the array - then greedily choose the elements that is element - last_element >= y
// O(NlogN), O(1)
int getLargestSubset(int n, vector<int>& v, int y) {
    if (n == 0) return 0; 

    sort(v.begin(), v.end());
    int last_element = v[0], answer = 1;
    for (int i = 1; i < n; i++) {
        if (v[i] - last_element >= y) {
            ++answer;
            last_element = v[i];
        }
    }

    return answer;
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, y; cin >> n >> y;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        
        cout << getLargestSubset(n, v, y) << '\n';
    }

    return 0;
}
