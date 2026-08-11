#include <bits/stdc++.h>
using namespace std;

/*
Amazon developers are working on a simple load-balancing algorithm across num_servers servers (indexed 0 to num_servers - 1). Initially, all servers have 0 assigned requests.RulesFor each request $i$ with IP hash requests[i]:The request must be assigned to the server with the minimum number of requests among servers in the range [0, requests[i]].If multiple servers in that range tie for the minimum number of requests, choose the one with the minimum server ID (smallest index).Once assigned, that server's request count increases by $1$.TaskReturn an array of integers representing the server ID assigned to each request.Constraints$1 \le \text{num\_servers} \le 10^5$$1 \le n \le 10^5$ (number of requests)$0 \le \text{requests}[i] < \text{num\_servers}$Sample CasesSample Case 0Input: num_servers = 5, requests = [4, 0, 2, 2]Output: [0, 0, 1, 2]Explanation:requests[0] = 4: Range [0..4], counts are [0,0,0,0,0]. Min count is 0 at server 0. Assigned to 0. Counts $\rightarrow$ [1,0,0,0,0].requests[1] = 0: Range [0..0], counts are [1,0,0,0,0]. Min count at server 0. Assigned to 0. Counts $\rightarrow$ [2,0,0,0,0].requests[2] = 2: Range [0..2], counts are [2,0,0,0,0]. Min count is 0 at server 1. Assigned to 1. Counts $\rightarrow$ [2,1,0,0,0].requests[3] = 2: Range [0..2], counts are [2,1,0,0,0]. Min count is 0 at server 2. Assigned to 2. Counts $\rightarrow$ [2,1,1,0,0].Sample Case 1Input: num_servers = 5, requests = [0, 1, 2, 3]Output: [0, 1, 2, 3]
Link - https://leetcode.com/discuss/post/6331313/amazon-oa-2025-sde-by-anonymous_user-eplv/
*/

// we cannot use priority queue here since it gives global maximum but here for each request[i] we doing ranged query and finding its maximum so priority queue would be O(n^2log(n))
// segment trees -> store (min_count, min_index) so if request count is same then we compare index for queries in log(n) -> nlog(num_servers), O(num_servers)

class SegmentTree {
    vector<pair<int, int>> tree;
    int n;
    const pair<int, int> INF = {1e9, 1e9};

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = { 0, start };
            return;
        }

        int middle = (start + end) / 2;
        build(2*node, start, middle);
        build(2*node+1, middle+1, end);
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }

    void update(int node, int index, int start, int end, int value) {
        if (start == end) {
            tree[node] = { value, start };
            return;
        }
        int middle = (start + end) / 2;
        if (index <= middle) {
            update(2*node, index, start, middle, value);
        } else {
            update(2*node+1, index, middle+1, end, value);
        }
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }

    pair<int, int> query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) {
            return INF;
        }
        if (left <= start && end <= right) {
            return tree[node];
        }
        int middle = (start + end) / 2;
        return min(query(2*node, start, middle, left, right), query(2*node+1, middle+1, end, left, right));
    }

    public:
    SegmentTree(int num_servers) {
        n = num_servers;
        tree.assign(4*n, { 0, 0 });
        build(1, 0, n - 1);
    }

    void update(int index, int value) {
        update(1, index, 0, n - 1, value);
    }

    pair<int, int> query(int left, int right) {
        return query(1, 0, n - 1, left, right); 
    }
};

vector<int> findRequestTarget(int num_servers, vector<int>& requests) {
    SegmentTree st(num_servers);
    vector<int> server_counts(num_servers, 0);
    vector<int> result;

    for (int request : requests) {
        pair<int, int> best = st.query(0, request);
        int target_server = best.second;
        result.push_back(target_server);
        server_counts[target_server]++;
        st.update(target_server, server_counts[target_server]);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int num_servers = 5;
        vector<int> requests = { 4, 0, 2, 2 };
        vector<int> answer = findRequestTarget(num_servers, requests);
        for (int server : answer) {
            cout << server << " ";
        }
        cout << '\n';
    }

    return 0;
}
