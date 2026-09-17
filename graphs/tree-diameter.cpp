#include <bits/stdc++.h>
using namespace std;

// this problem is to learn - centroid approach in minimum height tree problem
//
// problem statement: Given an unweighted tree, find the number of edges in its longest path. It's the direct match for your double-DFS/BFS code above — find the farthest node from any start, then the farthest node from that node; the distance between them is the diameter (and the midpoint of that path is the centroid, same as in MHT).
/*
Input: n = 4, edges = [[0,1],[1,2],[1,3]]
Output: 2
(longest path: 0-1-2 or 0-1-3 or 2-1-3, all 2 edges)

Input: n = 6, edges = [[0,1],[0,2],[0,3],[3,4],[4,5]]
Output: 4
(longest path: 1-0-3-4-5 or 2-0-3-4-5)

Input: n = 1, edges = []
Output: 0
(single node, no edges)

Input: n = 2, edges = [[0,1]]
Output: 1
*/
// in this approach we gurantee that from whichever node we start it would find the diameter. Finding farthest point from some arbitrary point say 'A' and then finding again from 'B' then 'A' - 'B' is the diameter. If we start from some endpoint already then it would directly find the diameter, while if we start from some middle node then after first DFS 'A' would be some endpoint and when we find farthest point from 'A' that would be another endpoint and hence diameter is found. O(V + E), O(V)
vector<vector<int>> adj;

pair<int, int> findDiameter(int node, int parent, int distance, pair<int, int>& farthest) {
    if (distance > farthest.second) {
        farthest = { node, distance };
    }

    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        findDiameter(neighbor, node, distance + 1, farthest);
    }

    return farthest;
}

int solve(int n, vector<vector<int>>& edges) {
    adj.resize(n);

    for (auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    pair<int, int> farthest = { 0, 0 };
    auto [A, distanceA] = findDiameter(0, -1, 0, farthest);

    farthest = { 0, 0 };
    auto [B, distanceB] = findDiameter(A, -1, 0, farthest);

    return distanceB;
}

int main() {
    return 0;
}
