#include <bits/stdc++.h> 
using namespace std;

class Node {
    public:
        int value;
        vector<Node*> neighbours;

        Node (int value) {
            this->value = value;
        }
};

unordered_map<Node*, Node*> cloned;
Node* clone(Node* node) {
    if (!node) return nullptr;
    if (cloned.count(node)) return cloned[node];

    Node* copy = new Node(node->value);
    cloned[node] = copy;

    for (Node* neighbour : node->neighbours) {
        copy->neighbours.push_back(clone(neighbour));
    }

    return copy;
}

// printing bfs of cloned graph
void bfs(Node* start) {
    unordered_set<Node*> visited;
    queue<Node*> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Node* node = q.front(); q.pop();
        cout << node->value << " -> ";
        for (Node* neighbour : node->neighbours) {
            cout << neighbour->value << " ";
            if (!visited.count(neighbour)) {
                q.push(neighbour);
                visited.insert(neighbour);
            }
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<Node*> nodes(n+1, nullptr);
        for (int i = 1; i <= n; i++) nodes[i] = new Node(i);

        // building the graph
        for (int i = 1; i <= n; i++) {
            Node* node = nodes[i];
            int k; cin >> k;
            for (int j = 0; j < k; j++) {
                int value; cin >> value;
                node->neighbours.push_back(nodes[value]); 
            }
        }
        cloned.clear();
        Node* copy = clone(nodes[1]);
        bfs(copy);
    }

    return 0;
}

