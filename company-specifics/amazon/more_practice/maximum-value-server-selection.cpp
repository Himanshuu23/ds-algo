#include <bits/stdc++.h>
using namespace std;

/*
Problem: Maximum Value Server Selection
Amazon's server room is organized as a rooted tree of n servers. Each server i has a processing value val[i] (can be negative — some servers carry maintenance overhead). Each server (except the root) has exactly one parent, connected by a rack cable.
You must select a subset of servers to activate for a batch job, subject to one rule: no two directly connected servers (parent–child) can both be active — an active cable between two active servers causes signal interference.
Return the maximum total processing value achievable from any valid subset. (The empty subset, value 0, is always valid, so the answer is never negative.)
Input: a general rooted tree — each Node has val and a list of children (not binary this time — any number of children per node).
struct Node {
    int val;
    vector<Node*> children;
};
Constraints
1 ≤ n ≤ 2×10^5
-10^4 ≤ val[i] ≤ 10^4
Example

        4
       / \
      1   5
     / \    \
    2   3   -6

Edges: 4–1, 4–5, 1–2, 1–3, 5–(-6)
Best subset: {4, 2, 3} — 4 and 1 aren't both selected, and 2/3's parent (1) isn't selected either, so no adjacent pair is active. 5 and -6 are both skipped since -6 is negative and not worth activating along with 5 alone being suboptimal here.
Output: 10
*/

// we have two choices -> take the current root, or skip it, if we take current root then we have to skip child, elsewise if we skip the root then we have two choices either take the child or skip it
// O(N), O(H)
struct Node {
    int value;
    vector<Node*> children;
};

pair<long long, long long> dfs(Node* root) {
    if (!root) return {0, 0};

    long long take_node = root->value;
    long long skip_node = 0;

    for (Node* child : root->children) {
        auto [take_child, skip_child] = dfs(child);

        take_node += skip_child;

        skip_node += max(take_child, skip_child);
    }

    return {take_node, skip_node};
}

long long maximumTotalProcessingValue(Node* root) {
    if (!root) return 0;

    auto [take_root, skip_root] = dfs(root);

    return max({ 0LL, take_root, skip_root });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
