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
    TreeNode* findMin(TreeNode* root) {
        while (root && root->left)
            root = root->left;
        return root;
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) {
            return nullptr;
        }

        // finding the node to be deleted
        if (root->val > key) {
            root-> left = deleteNode(root->left, key);
        } else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        } else {
            // found the node to delete
            // if node has single child
            if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            
            // node with two children + connecting the tree after deletion
            TreeNode* temp = findMin(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }

        return root;
    }
};

// iterative - O(h), O(1)
class Solution2 {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;

        TreeNode* parent = nullptr;
        TreeNode* current = root;
        
        // Find the node to delete
        while (current && current->val != key) {
            parent = current;
            if (current->val > key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        // Node doesn't exists in the tree
        if (!current) return root;

        // Node with only single or no child
        if (!current->left || !current->right) {
            TreeNode* child = current->left ? current->left : current->right;
            if (!parent) return child;
            if (parent->left == current) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else {
            // Node with two children
            TreeNode* par = nullptr; // parent of right subtree's min node -> next candidate after current is deleted -> min node in its right subtree - inorder successor

            TreeNode* toDelete = current;
            current = current->right;
            while (current->left) {
                par = current;
                current = current->left;
            }

            if (par) { // if there was a left traversal - moving that inorder successor to toDelete's position
                par->left = current->right;
                current->right = toDelete->right;
            }
            current->left = toDelete->left;

            if (!parent) return current; // if deleting root

            // if not deleting root then connecting back tree
            if (parent->left == toDelete) {
                parent->left = current;
            } else {
                parent->right = current;
            }
        }

        return root;
    }
};
