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

// recursive - O(h), O(h)
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) {
            return new TreeNode(val);
        }

        if (root->val > val)
            root->left = insertIntoBST(root->left, val);
        else
            root->right = insertIntoBST(root->right, val);

        return root;
    }
};

// iterative - O(h), O(1)
class Solution2 {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (!root) {
            return new TreeNode(val);
        }

        TreeNode* current = root;
        while (true) {
            if (current->val < val) {
                if (!current->right) {
                    current->right = new TreeNode(val);
                    return root;
                }
                current = current->right;
            } else {
                if (!current->left) {
                    current->left = new TreeNode(val);
                    return root;
                }
                current = current->left;
            }
        }
    }
};
