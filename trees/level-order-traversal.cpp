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

// using bfs - O(n), O(n)
vector<vector<int>> solve(Node* root) {
    vector<vector<int>> ans;
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        int currLevel = q.size();
        vector<int> level;
        for (int i = 0;  i < currLevel; i++) {
            Node* node = q.front(); q.pop();
            level.push_back(node->data);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        ans.push_back(level);
    }
    
    return ans;
}

// dfs - O(n), O(n)
class Solution {
public:
    vector<vector<int>> result;

    void dfs(Node* node, int depth) {
        if (!node) return;

        // if first time visiting a depth make an array for that level
        if (result.size() == depth) {
            result.push_back(vector<int>());
        }

        result[depth].push_back(node->data);
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
    }
    vector<vector<int>> levelOrder(Node* root) {
        dfs(root, 0);
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);
        root->right->left = new Node(5);
        root->right->right = new Node(6);

        vector<vector<int>> ans = solve(root);
        for (int i = 0; i < ans.size(); i++) {
            for (int j = 0; j < ans[i].size(); j++) {
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
