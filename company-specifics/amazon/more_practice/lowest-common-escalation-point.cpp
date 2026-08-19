#include <bits/stdc++.h>
using namespace std;

/*
Amazon's org chart is modeled as a binary tree of employees, where each node is an Employee with a unique id and pointers to left and right reports. For any incident, the on-call system needs to find the lowest-level manager who oversees both of two specific employees — i.e., their Lowest Common Ancestor.
Given the root of the tree and the ids of two employees p and q (both guaranteed to exist in the tree), return the id of their LCA.
Follow-up (Amazon likes to layer this in the same question): What if p or q might not exist in the tree? Modify your solution to return -1 in that case instead of a wrong/partial answer.
struct Employee {
    int id;
    Employee* left;
    Employee* right;
};
Constraints
1 ≤ n ≤ 10^5 nodes
All ids are unique
Tree is not a BST — cannot use value comparisons to prune, must handle general binary tree
Example

        3
       / \
      5   1
     / \  / \
    6  2 0   8
      / \
     7   4

p = 5, q = 4 → LCA = 5 (since 4 is in 5's subtree)
p = 6, q = 4 → LCA = 5
p = 7, q = 8 → LCA = 3
*/

struct Employee {
    int id;
    Employee* left;
    Employee* right;
};

// O(N), O(H) -> for the case if p and q guaranteed exist in the tree
Employee* lowestCommonEscalationPoint(Employee* root, Employee* p, Employee* q) {
    if (!root || root == p || root == q) return root;

    Employee* left = lowestCommonEscalationPoint(root->left, p, q);
    Employee* right = lowestCommonEscalationPoint(root->right, p, q);

    if (left && right) return root;
    return left ? left : right;
}

// handling if p or q or both are missing -> return -1 coz elsewise above approach would return p as LCA if q is missing which is incorrect
// new approach - each node counts how many (p or q are present) in self, its left subtree, its right subtree - where totalFound == 2 that deepest node is the answer. Now if p or q or both are missing count remains less than 2 so we return -1
// case: where p, q are present multiple times can't happen coz id of each employee is unique
// O(N), O(H)
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

int lowestCommonEscalationPoint(Employee* root, int p, int q) {
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

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
