#include <bits/stdc++.h>
using namespace std;

/*
You are given a binary tree containing $N$ nodes. A subset of nodes is called valid if no two selected nodes are directly connected by an edge (i.e., an independent set).Your task is to determine the total number of valid subsets that can be formed from the given binary tree. The empty subset is also considered valid.Input FormatThe binary tree is given as a collection of nodes where each node contains:An integer value.A pointer/reference to its left child.A pointer/reference to its right child.Note: You may assume that the given structure is a valid binary tree.Output FormatReturn the total number of valid subsets modulo $10^9 + 7$.ExampleConsider the following binary tree:Plaintext        1
       / \
      2   3
     / \
    4   5
Valid Subsets:{} (Empty subset){1}, {2}, {3}, {4}, {5}{1, 4}, {1, 5}{2, 3}{3, 4}, {3, 5}{3, 4, 5}Total Valid Subsets: 12Invalid Subsets (for reference):{1, 2} — Invalid because nodes 1 and 2 are directly connected.{2, 4} — Invalid because nodes 2 and 4 are directly connected.Constraints$1 \le N \le 2 \times 10^5$Return the answer modulo $10^9 + 7$.
*/

const int MOD = 1e9 + 7;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Tree + DP -> builds bottom up and returns a pair [selected, not selected] for every node representing the count of valid subsets in that node's subtree
// if select is true (current node's) then nor of its children can be included => selected = left not selected + right not selected
// if not selected then we can independently select the children => not selected = (left selected + left not selected) x (right selected + right not selected)
// base case = nullptr returns {0, 1} 0 ways to select but 1 way to select nothing -> empty set
// O(N), O(H) space, H -> height of the tree

// Returns {count_if_selected, count_if_not_selected}
pair<long long, long long> dfs(Node* root) {
    // Base Case: An empty subtree has 0 ways to select a node 
    // and 1 way to not select anything (the empty set).
    if (!root) {
        return {0, 1}; 
    }

    // Post-order traversal: calculate results for left and right subtrees
    auto [left_select, left_not_select] = dfs(root->left);
    auto [right_select, right_not_select] = dfs(root->right);

    // 1. If root IS selected:
    //    Neither left nor right child can be selected.
    long long selected = (left_not_select * right_not_select) % MOD;

    // 2. If root IS NOT selected:
    //    Left and right children can either be selected or not selected.
    long long left_total = (left_select + left_not_select) % MOD;
    long long right_total = (right_select + right_not_select) % MOD;
    long long not_selected = (left_total * right_total) % MOD;

    return {selected, not_selected};
}

int countValidSubsets(Node* root) {
    if (!root) return 1; // Empty tree has 1 valid subset: {}

    auto [root_selected, root_not_selected] = dfs(root);

    return (root_selected + root_not_selected) % MOD;
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
