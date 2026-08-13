#include <bits/stdc++.h>
using namespace std;

/*
You are given the root of a binary tree with a special modification: all the leaf nodes are modified to form a Doubly Linked List (DLL).
Rules & Definitions
For internal (non-leaf) nodes, standard binary tree pointers apply (left points to the left child, right points to the right child).
For leaf nodes, the pointers are repurposed for the DLL:
right points to the next leaf node in the linked list.
left points to the previous leaf node in the linked list.
A node node is identified as a leaf node if its right pointer is non-null and points to a neighbor whose left pointer points back to node (i.e., node->right->left == node), or vice-versa (node->left->right == node).
The height of the tree is defined as the maximum number of nodes along the path from the root down to any leaf node.
Task
Calculate and return the height of this special binary tree.
Example
Plaintext
       2
      / \
     4   7 
    / \   \
   6   5   9
      /
     1
Input: root pointing to node 2 (where leaves 6, 1, and 9 are connected as a doubly linked list: 6 <-> 1 <-> 9).
Output: 4
Explanation:
The longest path from root to leaf is 2 -> 4 -> 5 -> 1, which contains 4 nodes.
Leaves can be identified using the condition: node->right && node->right->left == node.
Link - https://takeuforward.org/interview-experience/amazon-interview-experience-sde-intern-set-5
*/

class Node {
    public:
    int value;
    Node* left, *right;

    Node(int value) : value(value), left(nullptr), right(nullptr) {
    }
};

// O(N) - each node visited once, O(H) - max height that recursion stack holds
int getHeight(Node* root) {
    if (!root) return 0;

    bool isLeafNode = (root->right && root->right->left == root) || (root->left && root->left->right == root);
    if (isLeafNode) return 1;

    return 1 + max(getHeight(root->left), getHeight(root->right));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        Node* root = new Node(2);
        Node* node2 = new Node(4);
        Node* node3 = new Node(7);
        Node* node4 = new Node(6);
        Node* node5 = new Node(5);
        Node* node6 = new Node(9);
        Node* node7 = new Node(1);

        root->left = node2;
        root->right = node3;
        node2->left = node4;
        node2->right = node5;
        node3->right = node6;
        node5->left = node7;
        node3->right = node6;
        
        node4->right = node7;
        node7->left = node4;
        node7->right = node6;
        node6->left = node7;
        
        cout << getHeight(root) << '\n';
    }

    return 0;
}
