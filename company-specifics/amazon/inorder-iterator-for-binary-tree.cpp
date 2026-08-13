#include <bits/stdc++.h>
using namespace std;

/*
Design an iterator class that iterates over the nodes of a Binary Tree in an Inorder sequence (Left -> Root -> Right).The iterator should support the following operations:BinaryTreeIterator(TreeNode* root): Initializes the iterator object with the root of the binary tree.next(): Returns the next integer in the inorder traversal sequence.hasNext(): Returns true if there are still elements remaining in the inorder traversal, otherwise false.TaskImplement the iterator such that calls to next() and hasNext() perform controlled on-demand traversal of the tree.ExampleTree Structure:Plaintext           8 
         /   \                 
        3     9
      /   \             
     2     4                                       
            \                            
             5 
Operations & Outputs:next() $\rightarrow$ 2hasNext() $\rightarrow$ truenext() $\rightarrow$ 3next() $\rightarrow$ 4next() $\rightarrow$ 5hasNext() $\rightarrow$ truenext() $\rightarrow$ 8next() $\rightarrow$ 9hasNext() $\rightarrow$ falseOutput Sequence: [2, true, 3, 4, 5, true, 8, 9, false]Constraints & GoalsTime Complexity: Average $\mathcal{O}(1)$ time per next() and hasNext() call.Space Complexity:Standard Stack Approach: $\mathcal{O}(H)$ extra space, where $H$ is the height of the tree.Advanced Approach: $\mathcal{O}(1)$ extra space using Morris Traversal.
Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/
*/

// brute force - pre calculate the inorder in constructor then respond to calls in O(1) using an index variable that corresponds to the next(), hasNext() calls - but bad approach since O(N) space consumed, also it breaks the actual use of an iterator that is on demand processing, if tree has 10^6 nodes then we can only call next() two times - like if we only wanna call 2 times then remaining 999, 998 nodes waste - constructor spends O(n) time and memory

// using controlled stacks - O(H) - inorder traversal - always next node to visit is leftmost unvisited node. We maintain a stack that holds this left branch, top of stack -> next leftmost node 
// When we pop check if topmost had right child coz next left childrens would be those only
// space - O(H) - stack hold root to leaf - left path of a node, hasNext() and next() -> O(1)
class Node {
    public:
        int value;
        Node* left, *right;

        Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

class BSTIterator {
    private:
        stack<Node*> st;

        void pushAllLeft(Node* node) {
            while (node != nullptr) {
                st.push(node);
                node = node->left;
            }
        }

    public:
        BSTIterator(Node* root) {
            pushAllLeft(root);
        }
        
        int next() {
            Node* topNode = st.top();
            st.pop();

            if (topNode->right != nullptr) {
                pushAllLeft(topNode->right);
            }

            return topNode->value;
        }

        bool hasNext() {
            return !st.empty();
        }
};

// Using Morris Traversal - Inorder in O(N) time and O(1) space
// next() -> O(1) but overall time O(N) for traversing each node and O(1) space though
// just keeping a current pointer and finding the unvisited leftmost through it 
class BSTIterator2 {
    private:
        Node* current;

    public:
        BSTIterator2(Node* root) {
            current = root;
        }

        bool hasNext() {
            return current != nullptr;
        }

        int next() {
            int value = -1;

            while (current != nullptr) {
                if (current->left == nullptr) {
                    value = current->value;
                    current = current->right;
                    break; // found the next element
                } else {
                    // find predecessor
                    Node* previous = current->left;
                    while (previous->right != nullptr && previous->right != current) {
                        previous = previous->right;
                    }

                    if (previous->right == nullptr) {
                        previous->right = current; // create thread
                        current = current->left; // continue moving forward
                    } else {
                        previous->right = nullptr; // destroy thread
                        value = current->value;
                        current = current->right;
                        break; // found the next element
                    }
                }
            }

            return value;
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
