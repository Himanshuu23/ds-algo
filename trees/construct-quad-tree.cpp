#include <bits/stdc++.h>
using namespace std;

// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

// checking each grid n^2 and total grids possible logn -> O(n^2logn), O(logn) -> space for recursion stack
class Solution {
private:
// representing each grid with its top left cell
// dimensions would keep going n -> n / 2 -> n / 4 -> ... 1
// if entire grid is already same then we don't have to divide it either way -> can be considered as one complete leaf node -> called pruning
    Node* dfs(vector<vector<int>>& grid, int n, int r, int c) { // n -> dimension of grid, r and c -> top left of that grid
    // checking if all same 
        bool allSame = true;
        for (int i = 0; i < n && allSame; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[r][c] != grid[r + i][c + j]) {
                    allSame = false;
                    break;
                }
            }
        }

        if (allSame) {
            return new Node(grid[r][c] == 1, true); // leaf node
        }

        // all different -> means its not leaf node - has four children
        int middle = n / 2;
        Node* topLeft = dfs(grid, middle, r, c);
        Node* topRight = dfs(grid, middle, r, c + middle);
        Node* bottomLeft = dfs(grid, middle, r + middle, c);
        Node* bottomRight = dfs(grid, middle, r + middle, c + middle);

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }

public:
    Node* construct(vector<vector<int>>& grid) {
        return dfs(grid, grid.size(), 0, 0);
    }
};

// optimization to n^2 : instead of checking uniformity first we should first build the four child and if they are all same means we can merge them and hence we don't have to check allSame for each level
class Solution2 {
private:
    Node* dfs(vector<vector<int>>& grid, int n, int r, int c) {
        if (n == 1) {
            return new Node(grid[r][c] == 1, true);
        }

        int middle = n / 2;
        Node* topLeft = dfs(grid, middle, r, c);
        Node* topRight = dfs(grid, middle, r, c + middle);
        Node* bottomLeft = dfs(grid, middle, r + middle, c);
        Node* bottomRight = dfs(grid, middle, r + middle, c + middle);

        if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf && topLeft->val == topRight->val && topLeft->val == bottomLeft->val && topLeft->val == bottomRight->val) {
            return new Node(topLeft->val, true);
        }

        return new Node(false, false, topLeft, topRight, bottomLeft, bottomRight);
    }

public:
    Node* construct(vector<vector<int>>& grid) {
        return dfs(grid, grid.size(), 0, 0);
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
