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


// handling if p or q or both are missing -> return -1 coz elsewise above approach would return p as LCA if q is missing which is incorrect
// new approach - each node counts how many (p or q are present) in self, its left subtree, its right subtree - where totalFound == 2 that deepest node is the answer. Now if p or q or both are missing count remains less than 2 so we return -1
// case: where p, q are present multiple times can't happen coz id of each employee is unique
// O(N), O(H)

struct Employee {
    int id;
    Employee* left;
    Employee* right;
};

Employee* lcaNode = nullptr;

int countTargets(Employee* root, int p, int q) {
    if (!root) return 0;

    int self = (root->id == p || root->id == q) ? 1 : 0;
    int left = countTargets(root->left, p, q);
    int right = countTargets(root->right, p, q);

    int totalFound = self + left + right;

    if (totalFound == 2 && !lcaNode) {
        lcaNode = root;
    }

    return totalFound;
}

int lowestCommonAncestor(Employee* root, int p, int q) {
    lcaNode = nullptr;
    int total = countTargets(root, p, q);

    if (total == 2 && lcaNode) {
        return lcaNode->id;
    }

    return -1;
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
