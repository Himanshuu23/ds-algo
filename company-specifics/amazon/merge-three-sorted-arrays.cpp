#include <bits/stdc++.h>
using namespace std;

/*
You are given three arrays of integers A, B, and C, where each array is individually sorted in non-decreasing order.TaskMerge all three arrays into a single sorted array S such that S contains all elements from A, B, and C in non-decreasing order.Input FormatAn integer array A sorted in non-decreasing order.An integer array B sorted in non-decreasing order.An integer array C sorted in non-decreasing order.Output FormatReturn a single integer array S containing all merged elements in sorted order.ExamplesExample 1Input:A = [1, 2, 3, 4, 5]B = [4, 5, 6]C = [7, 8, 9]Output: [1, 2, 3, 4, 4, 5, 5, 6, 7, 8, 9]Example 2Input:A = [1, 2, 3]B = [1, 2, 3]C = [2, 2, 3, 4]Output: [1, 1, 2, 2, 2, 2, 3, 3, 3, 4]Constraints$1 \le \vert{}A\vert{}, \vert{}B\vert{}, \vert{}C\vert{} \le 10^5$$-10^9 \le A[i], B[i], C[i] \le 10^9$
Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/
*/

// we can also do it using minHeap of size 3 -> log(3) = 1.53 - O(1) space, O(n) time
// three pointers - O(a + b + c), O(1)
vector<int> mergeThree(const vector<int>& A, const vector<int>& B, const vector<int>& C) {
    int i = 0, j = 0, k = 0;
    vector<int> result;

    while (i < A.size() || j < B.size() || k < C.size()) {
        int valueA = (i < A.size()) ? A[i] : INT_MAX;
        int valueB = (j < B.size()) ? B[j] : INT_MAX;
        int valueC = (k < C.size()) ? C[k] : INT_MAX;

        if (valueA <= valueB && valueA <= valueC) result.push_back(A[i++]);
        else if (valueB <= valueA && valueB <= valueC) result.push_back(B[j++]);
        else result.push_back(C[k++]);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int a, b, c; cin >> a >> b >> c;
        vector<int> A(a), B(b), C(c);
        for (int i = 0; i < a; i++) {
            cin >> A[i];
        }
        for (int i = 0; i < b; i++) {
            cin >> B[i];
        }
        for (int i = 0; i < c; i++) {
            cin >> C[i];
        }

        vector<int> answer = mergeThree(A, B, C);
        for (int x : answer) {
            cout << x << " ";
        }
        cout << '\n';
    }

    return 0;
}
