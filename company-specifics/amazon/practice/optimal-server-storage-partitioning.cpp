#include <bits/stdc++.h>
using namespace std;

/*
Amazon Web Services (AWS) is partitioning large data logs across secondary cloud storage nodes.You are given an array dataChunks of size $n$, where dataChunks[i] represents the total gigabytes of data in the $i^{\text{th}}$ log file. You are also given an integer $m$, representing the number of available cloud storage nodes.You must assign data to storage nodes according to these rules:No Mixed Nodes: Each node can hold data from at most one log file. (Data from different log files cannot be combined in the same node, but a single log file may be split across multiple nodes in any integer amounts).Node Limit: You can use at most $m$ nodes in total.Fair Allocation Goal: Every node used should receive at least $S$ gigabytes of data.Your task is to find the maximum possible integer value $S$ such that you can fully occupy at least $m$ nodes with at least $S$ gigabytes each. If it is impossible to fill $m$ nodes with at least $1$ gigabyte each, return 0.Input FormatdataChunks: An array of $n$ integers.m: An integer representing the number of storage nodes required.Output FormatReturn a single long long integer representing the maximum minimum node capacity $S$.Constraints$1 \le n \le 10^5$$1 \le \text{dataChunks}[i] \le 10^9$$1 \le m \le 10^9$Example 1Input:n = 4dataChunks = [4, 7, 12, 6]m = 5Output: 5Explanation:If we set target capacity $S = 5$:dataChunks[0] = 4: Cannot form any node of size $5$ ($\lfloor 4/5 \rfloor = 0$).dataChunks[1] = 7: Can form $1$ node of size $5$ ($\lfloor 7/5 \rfloor = 1$, leaving $2$ GB unused).dataChunks[2] = 12: Can form $2$ nodes of size $5$ ($\lfloor 12/5 \rfloor = 2$, leaving $2$ GB unused).dataChunks[3] = 6: Can form $1$ node of size $5$ ($\lfloor 6/5 \rfloor = 1$, leaving $1$ GB unused).Total nodes created of size $\ge 5$ is $0 + 1 + 2 + 1 = 4$ nodes.Wait, if $S = 5$ gives $4$ nodes, we need $m = 5$ nodes!Let's check $S = 4$:4: $1$ node7: $1$ node12: $3$ nodes6: $1$ nodeTotal = $1 + 1 + 3 + 1 = 6 \ge 5$ nodes.So for $m = 5$, $S = 4$ is achievable.Example 2Input:n = 3dataChunks = [15, 20, 10]m = 4Output: 10Explanation:If $S = 10$:15 $\rightarrow 1$ node of $10$20 $\rightarrow 2$ nodes of $10$10 $\rightarrow 1$ node of $10$Total nodes formed = $1 + 2 + 1 = 4$ nodes. Exactly matches $m = 4$.
*/

// O(nlog(max(data)), O(n)
bool canMakeMNodes(vector<long long>& data, int m, int S) {
    if (S == 0) return false;
    long long nodes = 0;
    for (long long d : data) {
        nodes += (d / S);
    }
    return nodes >= m;
}

int partitionServer(vector<long long>& data, int m) {
    long long low = 1, high = 0;
    for (long long d : data) {
        high = max(high, d);
    }

    long long answer = 0;
    while (low <= high) {
        long long middle = low + (high - low) / 2;
        if (canMakeMNodes(data, m, middle)) {
            answer = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
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
        int n, m; cin >> n >> m;
        vector<long long> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        cout << partitionServer(v, m) << '\n';
    }

    return 0;
}
