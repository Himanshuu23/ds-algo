#include<bits/stdc++.h>
using namespace std;

// O(n^2), O(1) - transpose + reverse rows -> 90 degrees clockwise rotation - for n x n matrices
void solve(vector<vector<int>>& v) {
    int n = v.size();
    // transpose = swapping again every element's mirror in main diagonal
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            swap(v[i][j], v[j][i]);
        }
    }
    for (int i = 0; i < n; i++) {
        reverse(v[i].begin(), v[i].end());
    }
}

// O(n*m) - time and space - works for any dimension - on 90 degree clockwise rotation (i, j) -> (j, n-i-1), column becomes row and first row becomes last column
vector<vector<int>> rotate(vector<vector<int>>& v) {
    int n = v.size(), m = v[0].size();
    vector<vector<int>> result(m, vector<int> (n)); // dimensions would flip since row becomes col and vice-versa
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][n-i-1] = v[i][j];
        }
    }
    return result;
}
