#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// using dfs + dp - O(n), O(h)
class Solution {
    pair<int, int> dfs(TreeNode* root) {
        if (!root) return { 0, 0 };
        auto [take_left, skip_left] = dfs(root->left);
        auto [take_right, skip_right] = dfs(root->right);

        int take_root = root->val + skip_left + skip_right;
        int skip_root = max(take_left, skip_left) + max(take_right, skip_right);

        return { take_root, skip_root };
    }
public:
    int rob(TreeNode* root) {
        if (!root) return 0;

        auto [take_root, skip_root] = dfs(root);

        return max(take_root, skip_root);
    }
};
