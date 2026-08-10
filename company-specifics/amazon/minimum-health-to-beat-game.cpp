#include <bits/stdc++.h>
using namespace std;

/*
Amazon Prime Games requires a player to pass $n$ sequential rounds.Rules:Completing round $i$ costs power[i] health.The player's health must strictly stay greater than 0 at all times.The player can use armor once in any single round $i$, which reduces damage taken in that round by $\min(\text{armor}, \text{power}[i])$.Determine the minimum starting health required to complete all $n$ rounds.Sample CaseInput: power = [1, 2, 6, 7], armor = 5Optimal Armor Use: Use armor on round with max power ($7$). Damage reduced by $\min(5, 7) = 5$.Total Effective Damage: $(1 + 2 + 6 + 7) - 5 = 11$.Output: 12 (Since health must stay $> 0$, starting health = $11 + 1$).
Link - https://leetcode.com/discuss/post/6333650/amazon-oa-experience-sde1-seattle-by-ano-mnny/
*/

// greedy - use the armor on round with max cost - O(n), O(1)
long long solve(vector<int> cost, int armor) {
    int mx = INT_MIN;
    long long minHealth = 0;
    for (int x : cost) {
        minHealth += x;
        mx = max(mx, x);
    }

    minHealth -= min(armor, mx);
    return minHealth + 1;
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
        int armor; cin >> armor;
        cout << solve(v, armor) << '\n';
    }

    return 0;
}
