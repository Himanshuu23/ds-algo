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


int heightSolution2(Node* root) {
    if (!root) return 0;
    return 1 + max(heightSolution2(root->left), heightSolution2(root->right));
}

bool check_balancedSolution2(Node* root) {
    if (!root) return true;
    if (!check_balancedSolution2(root->left)) return false;
    if (!check_balancedSolution2(root->right)) return false;
    if (abs(heightSolution2(root->left) - heightSolution2(root->right)) > 1) return false;
    return true;
}

int height(Node* root) {
    if (!root) return 0;
    int left = height(root->left);
    int right = height(root->right);
    if (left == -1 || right == -1) return -1;
    if (abs(left - right) > 1) return -1;
    return 1 + max(left, right);
}

bool isBalanced(Node* root) {
    if (!root) return true;
    int ht = height(root);
    return (ht == -1) ? false : true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while (t--) {
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);

        cout << (isBalanced(root) ? "Yes" : "No") << "\n";
    }

    return 0;
}
