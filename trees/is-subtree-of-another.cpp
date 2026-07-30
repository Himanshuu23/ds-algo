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

// O(NxM) -> N - nodes of parent, M - nodes of child
bool isSameTree(Node* s, Node* t) {
    if (!s && !t) return true;
    if (!s || !t || s->data != t->data) return false;
    return isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
}

bool isSubtree(Node* root, Node* subRoot) {
    if (!root) return false;
    if (isSameTree(root, subRoot)) return true;
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

// O(N + M) solution - serializing + KMP
void serialize(Node* root, vector<string>& v) {
    if (!root) {
        v.push_back("#");
        return;
    }

    v.push_back(","+to_string(root->data));
    serialize(root->left, v);
    serialize(root->right, v);
}

vector<int> buildLps(vector<string>& pattern) {
    int i(1), j(0), m = pattern.size();
    vector<int> lps(m, 0);

    while (i < m) {
        if (pattern[i] == pattern[j]) {
            j++;
            lps[i] = j;
            i++;
        } else {
            if (j != 0) j = lps[j-1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

bool kmp(vector<string>& s, vector<string>& p) {
    int n = s.size(), m = p.size();
    vector<int> lps = buildLps(p);
    int i(0), j(0);
    while (i < n) {
        if (s[i] == p[j]) i++, j++;
        if (j == m) return true;
        else if (i < n && s[i] != p[j]) {
            if (j != 0) j = lps[j-1];
            else i++;
        }
    }

    return false;
}

bool isSubtreeAgain(Node* tree, Node* child) {
    if (!tree) return false;
    vector<string> parent, subTree;
    serialize(tree, parent);
    serialize(child, subTree);
    return kmp(parent, subTree);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = new Node(3);
    root->left = new Node(4);
    root->right = new Node(5);
    root->left->left = new Node(1);
    root->left->right = new Node(2);

    Node* subRoot = new Node(4);
    subRoot->left = new Node(1);
    subRoot->right = new Node(2);

    cout << (isSubtree(root, subRoot) ? "YES" : "NO") << '\n';

    return 0;
}
