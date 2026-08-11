#include <bits/stdc++.h>
using namespace std;

/*
There are $n$ host servers, where the throughput of the $i^{\text{th}}$ host server is given by host_throughput[i].RulesThe host servers must be grouped into clusters of size 3.The throughput of a cluster is defined as the median (the $2^{\text{nd}}$ element when sorted) of its 3 servers.Each server can belong to at most one cluster (some servers may remain unused if $n$ is not a multiple of 3).The total system throughput is the sum of the throughputs of all formed clusters.TaskCalculate the maximum possible total system throughput that can be achieved by forming $\lfloor n / 3 \rfloor$ clusters optimal for maximizing the median sums.ExamplesExample 1:Input: host_throughput = [4, 6, 3, 5, 4, 5]Output: 9Explanation: Form 2 clusters: [3, 4, 6] (median = 4) and [4, 5, 5] (median = 5). Total = $4 + 5 = 9$.Example 2:Input: host_throughput = [2, 3, 4, 3, 4]Output: 4Explanation: Form 1 cluster: [2, 4, 4] (median = 4). Unused servers: [3, 3]. Total = $4$.
Link - https://www.reddit.com/r/leetcode/comments/1htdjbf/amazon_oa_questions_w_solutions/
*/

// after sorting - make the triplets since pairing largest one with smallest one wouldn't help as they go to the end
// O(nlogn)
long long getMaxThroughput(vector<int>& host_throughput) {
    int n = host_throughput.size();
    int num_clusters = n / 3;
    long long throughput = 0;
    sort(host_throughput.begin(), host_throughput.end());
    int index = n - 2;
    for (int c = 0; c < num_clusters; c++) {
        throughput += host_throughput[index];
        index -= 2;
    }
    return throughput;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> host_throughput(n);
        for (int i = 0; i < n; i++) {
            cin >> host_throughput[i];
        }

        cout << getMaxThroughput(host_throughput) << '\n';
    }

    return 0;
}
