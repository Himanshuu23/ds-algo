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

// dfs - O(n), O(h)
class Solution {
    int result = 0;
    void dfs(TreeNode* root, int currentMax) {
        if (!root) return;
        if (root->val >= currentMax) {
            ++result;
            currentMax = root->val;
        }
        dfs(root->left, currentMax);
        dfs(root->right, currentMax);
    }
public:
    int goodNodes(TreeNode* root) {
        dfs(root, INT_MIN);
        return result;
    }
};

// bfs - O(n), O(h)
class Solution2 {
public:
    int goodNodes(TreeNode* root) {
        int answer = 0;
        queue<pair<TreeNode*, int>> q;
        int currentMaximum = INT_MIN;
        q.push({ root, currentMaximum });
        while (!q.empty()) {
            int level = q.size();
            for (int i = 0; i < level; i++) {
                auto [node, maxValue] = q.front();
                q.pop();
                if (node->val >= maxValue) {
                    ++answer;
                }
                if (node->left) {
                    q.push({node->left, max(maxValue, node->val)});
                }
                if (node->right) {
                    q.push({node->right, max(maxValue, node->val)});
                }
            }
        }

        return answer;
    }
};
