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

void convertToDLL(Node* root, Node*& prev, Node*& head) {
    if (!root) return;

    convertToDLL(root->left, prev, head);

    if (!prev) {
        head = root;
    } else {
        prev->right = root;
        root->left = prev;    
    }
    prev = root; // Move prev to current

    convertToDLL(root->right, prev, head);
}

Node* binaryTreeToDLL(Node* root) {
    Node* head = nullptr;
    Node* prev = nullptr;
    convertToDLL(root, prev, head);
    return head;
}

void printDLL(Node* head) {
    cout << "Doubly Linked List (in-order): ";
    while (head) {
        cout << head->data << " ";
        head = head->right;
    }
    cout << endl;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        Node* root = new Node(10);
        root->left = new Node(5);
        root->right = new Node(20);
        root->right->left = new Node(15);
        root->right->right = new Node(25);

        Node* dllHead = binaryTreeToDLL(root);
        printDLL(dllHead);
    }

    return 0;
}
