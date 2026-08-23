#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// inorder of BST is always sorted - O(n), O(n)
class Solution {
    vector<int> inorder;
    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->left);
        inorder.push_back(root->val);
        dfs(root->right);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        if (!root) return -1;
        dfs(root);
        return inorder[k-1];
    }
};

// optimization of approach above - instead of storing just count as u visit nodes - O(n), O(h) - recursion stack
class Solution2 {
    int count = 0;
    int answer = 0;
    void dfs(TreeNode* root, int k) {
        if (!root) return;
        dfs(root->left, k);
        count++;
        if (count == k) {
            answer = root->val;
            return;
        }
        dfs(root->right, k);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        if (!root) return -1;
        dfs(root, k);
        return answer;
    }
};

// morris traversal - O(n), O(1) - we cannot return early since the threads need to be removed back so tree isn't modified
class Solution3 {
public:
    int kthSmallest(TreeNode* root, int k) {
        int count = 0, answer = -1;
        TreeNode* current = root;
        while (current) {
            if (current->left == nullptr) {
                count++;
                if (count == k) {
                    answer = current->val;
                }
                current = current->right;
            } else {
                TreeNode* previous = current->left;
                while (previous->right && previous->right != current) {
                    previous = previous->right;
                }

                if (previous->right == nullptr) {
                    previous->right = current;
                    current = current->left;
                } else {
                    previous->right = nullptr;
                    count++;
                    if (count == k) {
                        answer = current->val;
                    }
                    current = current->right;
                }
            }
        }

        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
