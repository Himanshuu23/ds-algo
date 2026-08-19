#include <bits/stdc++.h>
using namespace std;

/*
   An automated Amazon warehouse aisle has $N$ inventory slots represented by an integer array inventory, where inventory[i] represents the item ID at 1-based index $i$. A slot is defined as perfect if inventory[i] == i.You are allowed to remove any number of items from the array. When an item is removed, all items to its right shift one position to the left (their 1-based indices decrease by 1). Return the maximum number of perfect slots achievable after performing any number of item removals.Constraints$1 \le N \le 2000$$1 \le \text{inventory}[i] \le 2000$Sample Test CasesExample 1:PlaintextInput: inventory = [2, 1, 4, 3, 4]
Output: 3
Explanation:Remove inventory[0] (value 2) $\rightarrow$ array becomes [1, 4, 3, 4]Remove inventory[1] (value 4) $\rightarrow$ array becomes [1, 3, 4]Indices (1-based) are now 1, 2, 3.Slot 1 (1 == 1), Slot 2 (3 != 2), Slot 3 (4 != 3) $\rightarrow$ Wait, if we remove inventory[0] (2) and inventory[2] (3 from original [2,1,4,3,4]), we get [1, 4, 4] with 1-based indices 1, 2, 3.Optimal removals leave 3 perfect slots.
*/

// for each item we have two choices -> delete it or don't delete it. dp[i][k] => max score achievable with k deletions made.
// if we delete ith item then total deletions become k, and we get dp[i-1][k-1] only -> choose max of each possible deletions
// else we keep the element hence if after k deletions -> position of ith element => dp[i][k] = if it matches new position i - k then +1 else no just take previous answer
// O(n^2)
int maxPerfectSlots(int n, vector<int>& v) {
    vector<vector<int>> dp(n+1, vector<int> (n + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <= i; k++) {
            // keep element i
            int new_position = i - k;
            int gain = (new_position > 0 && v[i-1] == new_position) ? 1 : 0;
            dp[i][k] = dp[i-1][k] + gain;
            // delete element i
            if (k > 0) {
                dp[i][k] = max(dp[i][k], dp[i-1][k-1]);
            }
        }
    }

    int answer = 0;
    for (int k = 0; k <= n; k++) {
        answer = max(answer, dp[n][k]);
    }

    return answer;
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

        cout << maxPerfectSlots(n, v) << '\n';
    }

    return 0;
}
