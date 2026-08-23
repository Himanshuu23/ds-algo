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

// dfs - O(n^2), O(n)
class Solution {
private:
    int answer = INT_MIN;

    // provides max path through a node - Downward Path (path can be node + left subtree, node + right subtree) - Maximum sum starting from each node
    int getMax(TreeNode* root) {
        if (!root) return 0;
        int left = getMax(root->left);
        int right = getMax(root->right);
        int path = root->val + max(left, right);
        return max(0, path);
    }

    // trying all possible nodes and finding the maximum sum
    void dfs(TreeNode* root) {
        if (!root) return;
        int left = getMax(root->left);
        int right = getMax(root->right);
        answer = max(answer, root->val + left + right);
        dfs(root->left);
        dfs(root->right);
    }

public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return answer;
    }
};

// O(n), O(n)
class Solution2 {
public:
    // optimization to previous approach - earlier for each node we were repeatedly doing same work of finding best path through that node and also finding max sum through that node
    // Here doing both in one go
    int dfs(TreeNode* root, int& answer) {
        if (!root) return 0;

        int leftMax = max(dfs(root->left, answer), 0);
        int rightMax = max(dfs(root->right, answer), 0);

        answer = max(answer, root->val + leftMax + rightMax);
        return root->val + max(leftMax, rightMax);
    }

    int maxPathSum(TreeNode* root) {
        int answer = root->val;
        dfs(root, answer);
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
