/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node (int val) : data(val), left(nullptr), right(nullptr) {}
};

// dfs - O(n^2), O(n)
class Solution {
public:
    Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty()) {
            return nullptr;
        }

        Node* root = new Node(preorder[0]);

        // finding the index of current root
        auto middle = find(inorder.begin(), inorder.end(), preorder[0]) - inorder.begin();

        // all roots in its left subtree
        vector<int> left_preorder(preorder.begin() + 1, preorder.begin() + middle + 1);
        // all roots in its right subtree
        vector<int> right_preorder(preorder.begin() + middle + 1, preorder.end());

        // all elements in its left subtree
        vector<int> left_inorder(inorder.begin(), inorder.begin() + middle);

        // all elements in its right subtree
        vector<int> right_inorder(inorder.begin() + middle + 1, inorder.end());

        root->left = buildTree(left_preorder, left_inorder);
        root->right = buildTree(right_preorder, right_inorder);

        return root;
    }
};

unordered_map<int, int> mp;
int preOrderIndex(0);

// dfs + hashmap - O(n), O(n)
Node* build(const vector<int>& preorder, int left, int right) {
    if (left > right) return nullptr;
    int rootVal = preorder[preOrderIndex++];
    Node* root = new Node(rootVal);
    int index = mp[rootVal];

    root->left = build(preorder, left, index - 1);
    root->right = build(preorder, index + 1, right);

    return root;
}

Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
    for (int i = 0; i < inorder.size(); i++)
        mp[inorder[i]] = i;

    return build(preorder, 0, inorder.size() - 1);
}

// optimization of approach above - we don't need hashmap to get the next node to build - we can keep two left and right limits till where we have to build the current node. We can get the left limit using preorder and right using inorder
// O(n), O(n)
class Solution2 {
public:
    int preorder_index = 0, inorder_index = 0;
    Node* dfs(vector<int>& preorder, vector<int>& inorder, int limit) {
        if (preorder_index >= preorder.size()) return nullptr; // right subtree completed!

        // left subtree completed!
        if (inorder[inorder_index] == limit) {
            inorder_index++; // move to later root
            return nullptr;
        }

        Node* root = new Node(preorder[preorder_index++]);
        root->left = dfs(preorder, inorder, root->data);
        root->right = dfs(preorder, inorder, limit);
        return root;  
    }
    
    Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return dfs(preorder, inorder, INT_MAX);
    }
};

void print_inorder(Node* root) {
    if (!root) return;
    print_inorder(root->left);
    cout << root->data << " ";
    print_inorder(root->right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        vector<int> preorder = {3, 9, 20, 15, 7};
        vector<int> inorder = {9, 3, 15, 20, 7};
        Node* root = buildTree(preorder, inorder);
        print_inorder(root);
        cout << endl;
    }

    return 0;
}
