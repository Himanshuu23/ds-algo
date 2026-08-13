#include <bits/stdc++.h>
using namespace std;

/*
Given the root of a Binary Tree, calculate the vertical sum of all nodes that lie in the same vertical line (column). The output should contain the vertical sums ordered from the leftmost column to the rightmost column.DefinitionsAssign a Horizontal Distance ($HD$) to each node:Root node has $HD = 0$.Left child has $HD = \text{parent's } HD - 1$.Right child has $HD = \text{parent's } HD + 1$.All nodes with the same $HD$ belong to the same vertical line.ExampleInput Tree:Plaintext           8
         /   \                
        3     9
      /   \                     
     2     4                      
            \                            
             5
Horizontal Distance Calculation:$HD = -2$: Node 2 $\rightarrow \text{Sum} = 2$$HD = -1$: Node 3 $\rightarrow \text{Sum} = 3$$HD = 0$: Nodes 8, 4 $\rightarrow \text{Sum} = 8 + 4 = 12$$HD = +1$: Nodes 9, 5 $\rightarrow \text{Sum} = 9 + 5 = 14$Output:[-2: 2, -1: 3, 0: 12, 1: 14] (or ordered array [2, 3, 12, 14])
Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/
*/

class Node {
    public:
        int value;
        Node* left, *right;

        Node(int value) : value(value), left(nullptr), right(nullptr) {}
};

// O(N), min_distance and max_distance just to print in sorted order
// space -> O(K) for map where K <= N and O(H) for the recursion stack
void findVerticalSum(Node* root, int distance, int& min_distance, int& max_distance, unordered_map<int, int>& sum) {
    if (!root) return;
    sum[distance] += root->value;
    min_distance = min(min_distance, distance);
    max_distance = max(max_distance, distance);

    findVerticalSum(root->left, distance - 1, min_distance, max_distance, sum);
    findVerticalSum(root->right, distance + 1, min_distance, max_distance, sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        Node* root = new Node(8);
        Node* node2 = new Node(3);
        Node* node3 = new Node(9);
        Node* node4 = new Node(2);
        Node* node5 = new Node(4);
        Node* node6 = new Node(5);

        root->left = node2;
        root->right = node3;
        node2->left = node4;
        node2->right = node5;
        node5->right = node6;

        unordered_map<int, int> sum;
        int min_distance = INT_MAX, max_distance = INT_MIN;
        findVerticalSum(root, 0, min_distance, max_distance, sum);
        for (int i = min_distance; i <= max_distance; i++) {
            if (sum.find(i) != sum.end()) {
                cout << i << " -> " << sum[i] << '\n';
            }
        }
    }

    return 0;
}
