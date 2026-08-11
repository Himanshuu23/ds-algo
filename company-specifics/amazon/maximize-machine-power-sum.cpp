#include <bits/stdc++.h>
using namespace std;

/*
There are $n$ machines, where the $i^{\text{th}}$ machine contains a list of power units.Rules & DefinitionsThe effective power of a machine is defined as the minimum value among all power units currently assigned to it.You can reallocate power units between machines subject to the following rules:Each machine can donate at most 1 power unit to another machine.A machine can receive unlimited power units.The total power is the sum of the effective powers of all $n$ machines.TaskFind the maximum possible total power across all machines after optimal reallocation of power units.ExampleInput: machines = [[1, 5], [2, 3], [1, 0]]Initial Powers:Machine 0: $\min(1, 5) = 1$Machine 1: $\min(2, 3) = 2$Machine 2: $\min(1, 0) = 0$Total Initial Power = $1 + 2 + 0 = 3$
Link - https://www.reddit.com/r/leetcode/comments/1lz8kgv/bombed_amazon_oa/
*/

// greedy - we find the machine with smallest min -> we give others smallest machine to this machine and also we can only donate just once so second smallest of rest other machines and cost of this sink machine is the answer
// O(nlogm) where n is total machines and m is max units in each machines
long long getMaximumPowerSum(vector<vector<int>>& machines) {
    int n = machines.size();

    // sorting each machine's power units
    for (int i = 0; i < n; i++) {
        sort(machines[i].begin(), machines[i].end());
    }

    // finding sink
    int sink_index = 0;
    for (int i = 0; i < n; i++) {
        if (machines[i][0] < machines[sink_index][0]) {
            sink_index = i;
        }
    }

    long long total_power = machines[sink_index][0];
    for (int i = 0; i < n; i++) {
        if (i != sink_index) {
            total_power += (machines[i].size() > 1 ? machines[i][1] : machines[i][0]);
        } 
    }

    return total_power;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        vector<vector<int>> machines = {{1, 5}, {2, 3}, {1, 0}};
        cout << getMaximumPowerSum(machines) << '\n';
    }

    return 0;
}
