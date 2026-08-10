#include <bits/stdc++.h>
using namespace std;

/*
There are total_servers connected in a circular network numbered $1$ to total_servers (where server $1$ is connected to $2$, $2$ to $3$, ..., and total_servers connects back to $1$).A subset of $n$ servers needs to share data with each other. Moving data between any two directly connected adjacent servers takes $1$ unit of time. You must start at one server from the given array and visit all other target servers in the array.Find the minimum time required to transfer data to all target servers.Input Parameters:total_servers: An integer representing the total number of servers in the ring network ($1 \le \text{total\_servers} \le 10^9$).servers: An array of $n$ integers representing the servers that need data synchronization ($1 \le n \le 10^5$).Key Insight & Optimal Logic:Sort the servers array.The optimal path will always form a contiguous segment of the ring that covers all $n$ target servers, leaving out the largest single gap between adjacent target servers.$\text{Minimum Time} = \text{total\_servers} - \text{maximum gap between consecutive target servers in the ring}$.Sample CasesSample Case 0:Input: total_servers = 5, servers = [1, 5]Output: 1Explanation: Distance going directly between $1$ and $5$ is $1$ unit of time.Sample Case 1:Input: total_servers = 10, servers = [4, 6, 2, 9]Output: 7Explanation: Sorted servers are [2, 4, 6, 9]. The gaps are:$4 - 2 = 2$$6 - 4 = 2$$9 - 6 = 3$Wrap-around gap: $10 - 9 + 2 = 3$Max gap $= 3$. Result $= 10 - 3 = 7$.
Link - https://leetcode.com/discuss/post/5011657/amazon-oa-new-grad-by-anonymous_user-fdah/
*/

// while traversing we travel each server continously but we can skip one gap -> for min time - skip the maximum gap.
// O(nlogn), O(1)
int solve(int total_servers, vector<int>& servers, int n) {
    if (n == 1) return 0;
    sort(servers.begin(), servers.end());
    int mx = total_servers - servers.back() + servers[0]; // wrap around gap -> last server to first server
    for (int i = 0; i < n - 1; i++) {
        mx = max(mx, servers[i+1] - servers[i]);
    }

    return total_servers - mx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int total_servers; cin >> total_servers;
        int n; cin >> n;
        vector<int> servers(n);
        for (int i = 0; i < n; i++) {
            cin >> servers[i];
        }
        cout << solve(total_servers, servers, n) << '\n';
    }

    return 0;
}
