#include <bits/stdc++.h>
using namespace std;

// brute force: O(rows*cols)
bool bruteForce(vector<vector<int>>& v, int x) {
    int n = v.size(), m = v[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (v[i][j] == x) {
                return true;
            }
        }
    }
    return false;
}

// binary search - O(n*log(m))
bool usingBinarySearch(vector<vector<int>>& v, int target) {
    for (auto& row : v) {
        int low = 0, high = (int)row.size() - 1;
        while (low <= high) {
            int middle = low + (high - low) / 2;
            if (row[middle] == target) return true;
            else if (row[middle] < target) low = middle + 1;
            else high = middle - 1;
        }
    }
    return false;
}

// staircase searching: O(n + m), O(1)
// on going down the column or right the row the value of elements would be in ascending order
bool staircase(vector<vector<int>>& v, int target) {
    int n = v.size(), m = v[0].size();
    int r = 0, c = m - 1;
    while (r < n && c >= 0) {
        if (v[r][c] == target) {
            return true;
        } else if (v[r][c] < target) {
            r++;
        } else {
            c--;
        }
    }
    return false;
}

int main() {

    return 0;
}
