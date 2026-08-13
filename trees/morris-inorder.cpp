#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int value;
        Node* left, *right;
        
        Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

// O(N) inorder traversal in O(1) space complexity - Threaded Binary Tree (basically creating temporary threads to go back up the path to parent from child - no stack needed)
void morrisInorder(Node* root) {
    Node* current = root;

    while (current != nullptr) {
        if (current->left == nullptr) {
            cout << current->value << " ";
            current = current->right;
        } else {
            // find inorder predecessor
            Node* previous = current->left;
            while (previous->right != nullptr && previous->right != current) {
                previous = previous->right;
            }

            if (previous->right == nullptr) {
                previous->right = current; // create thread
                current = current->left; // continue moving left
            } else {
                // we have thread already
                previous->right = nullptr; // destroy thread
                cout << current->value << " ";
                current = current->right;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
