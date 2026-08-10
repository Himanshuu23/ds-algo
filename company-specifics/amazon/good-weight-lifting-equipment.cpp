#include <bits/stdc++.h>
using namespace std;

/*
You are given an array blocks of $n$ distinct integers representing the weights of stacked blocks from top to bottom ($0$-indexed or $1$-indexed).Equipment is defined as good if:The lightest block (minimum element) is at the top (index 0).The heaviest block (maximum element) is at the bottom (index n - 1).In one move, you can swap any two adjacent elements in the array.Task:Return the minimum number of moves required to make the weight lifting equipment "good".Constraints:$2 \le n \le 10^5$$1 \le \text{blocks}[i] \le 10^9$All elements in blocks are distinct.Sample CasesSample Case 0:Input: blocks = [2, 4, 3, 1, 6]Output: 3Explanation:The minimum element is 1 at index $3$.The maximum element is 6 at index $4$ (already at the end).Shift 1 to index $0$ via adjacent swaps: [2, 4, 3, 1, 6] $\rightarrow$ [2, 4, 1, 3, 6] $\rightarrow$ [2, 1, 4, 3, 6] $\rightarrow$ [1, 2, 4, 3, 6] ($3$ swaps).Sample Case 1:Input: blocks = [4, 11, 9, 10, 12]Output: 0Explanation: Min element 4 is already at the start, and max element 12 is already at the end.
Link - https://leetcode.com/discuss/post/4749861/amazon-oa-by-anonymous_user-1yoe/
*/

// O(N), O(1) - if min index < max index -> answer = swap each independently, if min index > mx index means they would cross each other once while swapping so that swap would be helpful and we count only as single swap since it's helping both
int solve(int n, vector<int>& blocks) {
    int mx_idx = 0, mn_idx = 0;
    for (int i = 1; i < n; i++) {
        if (blocks[i] > blocks[mx_idx]) mx_idx = i;
        if (blocks[i] < blocks[mn_idx]) mn_idx = i;
    }

    if (mn_idx > mx_idx) {
        return mn_idx + (n - 1 - mx_idx) - 1;
    } else {
        return mn_idx + (n - 1 - mx_idx);
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
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        cout << solve(n, v) << '\n';
    }

    return 0;
}
