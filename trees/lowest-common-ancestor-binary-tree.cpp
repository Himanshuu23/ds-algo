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

Node* justForBST(Node* root, Node* p, Node* q) { // O(h)
    if (!root) return nullptr;
    if (root->data > p->data && root->data > q->data) return justForBST(root->left, p, q);
    if (root->data < p->data && root->data < q->data) return justForBST(root->right, p, q);
    return root;
}


Node* solve(Node* root, Node* p, Node* q) {
    if (root == nullptr || root == p || root == q) return root;

    Node* left = solve(root->left, p, q);
    Node* right = solve(root->right, p, q);

    if (left && right) return root;
    return left ? left : right;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        Node* root = new Node(3);
        root->left = new Node(5);
        root->right = new Node(1);
        cout << solve(root, root->left, root->right)->data << endl;
    }

    return 0;
}
