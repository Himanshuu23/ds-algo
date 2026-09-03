#include <bits/stdc++.h> 
using namespace std;

class Node {
    public:
        int val;
        vector<Node*> neighbors;

        Node (int value) {
            val = value;
        }
};

// using dfs - O(V + E), O(V)
class Solution {
private:
    map<Node*, Node*> oldToNew;

    Node* dfs(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (oldToNew.count(node)) {
            return oldToNew[node];
        }

        Node* copy = new Node(node->val);
        oldToNew[node] = copy;

        for (Node* neighbor : node->neighbors) {
            copy->neighbors.push_back(dfs(neighbor));
        }

        return copy;
    }
public:
    Node* cloneGraph(Node* node) {
        return dfs(node);
    }
};

// using bfs - O(V + E), O(V)
class Solution2 {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        map<Node*, Node*> oldToNew;
        queue<Node*> q;
        oldToNew[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            for (Node* neighbor : current->neighbors) {
                if (oldToNew.find(neighbor) == oldToNew.end()) {
                    oldToNew[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                oldToNew[current]->neighbors.push_back(oldToNew[neighbor]);
            }
        }

        return oldToNew[node];
    }
};
