#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int n = mat[0].size(), answer(0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int value = mat[i][j];
                if (i == j) answer += value;
                if ((i != j) && (i + j == n-1)) answer += value;
            }
        }

        return answer;
    }
};
