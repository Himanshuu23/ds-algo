#include <bits/stdc++.h>
using namespace std;

/*
You are given an array of positive integers itemCost, where itemCost[i] represents the cost of the $i^{\text{th}}$ item.You need to group items into packages such that:Every package has the exact same total cost.Each package contains either 1 or 2 items (a single item or a pair of items).Each item can belong to at most one package.Return the maximum number of packages you can form with equal total cost.Constraints$1 \le n \le 10^5$$1 \le \text{itemCost}[i] \le 10^3$Sample CasesSample 1Input: itemCost = [1, 2, 3, 4, 5]Possible Packages:Target cost $S = 5$:Package 1: [5] (1 item)Package 2: [1, 4] (2 items)Package 3: [2, 3] (2 items)Output: 3Sample 2Input: itemCost = [2, 2, 2, 2]Possible Packages:Target cost $S = 2$: [2], [2], [2], [2] $\rightarrow$ 4 packagesTarget cost $S = 4$: [2, 2], [2, 2] $\rightarrow$ 2 packagesOutput: 4Core IntuitionSince each package has 1 or 2 items and $\text{itemCost}[i] \le 1000$:The target cost $S$ can range from $1$ up to $2000$.For every possible target sum $S$, count how many valid non-overlapping singletons (x == S) and pairs (x + y == S) you can greedily form using frequency maps or two pointers.Take the maximum count among all candidate target sums.
Link : https://leetcode.com/discuss/post/7112319/amazon-oa-sde-august-2025-by-anonymous_u-o8ee/
*/

// O(N + M^2), N -> lenght of itemCost and M -> max item of itemCost, Space - O(M) -> O(1000)
int solve(vector<int>& itemCost) {
    if (itemCost.size() == 0) return 0;
    int maxValue = 0;
    vector<int> frequency(1001, 0);
    for (int cost : itemCost) {
        frequency[cost]++;
        maxValue = max(maxValue, cost);
    }

    int answer = 0;
    for (int S = 1; S <= 2*maxValue; S++) {
        int currentPackages = 0;
        if (S <= 1000) {
            currentPackages += frequency[S];
        }

        for (int x = 1; x <= S/2; x++) {
            int y = S - x;
            if (x > 1000 || y > 1000) continue;
            if (x != y) {
                currentPackages += min(frequency[x], frequency[y]);
            } else {
                currentPackages += frequency[x]/2;
            }
        }

        answer = max(answer, currentPackages);
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
        cout << solve(v) << '\n';
    }

    return 0;
}
