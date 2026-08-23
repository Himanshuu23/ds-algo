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
    
    Node (int val) {
        data = val;
        left = right = nullptr;
    }
};

// other way -> inorder traversel of BST is a sorted array

// dfs - O(n), O(h) - recursion stack
bool isBST(Node* root, ll minVal, ll maxVal) {
    if (!root) return true;
    if (root->data <= minVal || root->data >= maxVal) return false;
    return isBST(root->left, minVal, root->data) && isBST(root->right, root->data, maxVal);
}

// bfs - O(n), O(h)
class Solution {
public:
    bool isValidBST(Node* root) {
        if (!root) return true;

        queue<tuple<Node*, int, int>> q;
        q.push({root, INT_MIN, INT_MAX});

        while (!q.empty()) {
            auto [node, left, right] = q.front();
            q.pop();
            
            if (left >= node->data || right <= node->data) {
                return false;
            }

            if (node->left) {
                q.push({node->left, left, node->data});
            }

            if (node->right) {
                q.push({node->right, node->data, right});
            }
        }

        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(2);
    root->left->right = new Node(7);
    root->right->left = new Node(12);
    root->right->right = new Node(20);

    if (isBST(root, LLONG_MIN, LLONG_MAX)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
