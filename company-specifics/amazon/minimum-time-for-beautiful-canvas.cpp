#include <bits/stdc++.h>
using namespace std;

/*
You are given a grid of dimensions $n \times m$ (initially all white cells) and an integer $k$.Each minute $i$ (starting from minute $1$), a specific cell paint[i-1] is painted black. The order of cell paintings is given by a 2D array paint of size $n \cdot m \times 2$ (using $1$-based cell coordinates).The canvas is defined as beautiful if there exists at least one $k \times k$ subgrid where all cells inside it are painted black.Task:Return the minimum time (in minutes) required for the canvas to become beautiful.Constraints:$1 \le n, m \le 750$$1 \le k \le \min(n, m)$$1 \le \text{paint}[i][0] \le n$$1 \le \text{paint}[i][1] \le m$All coordinates in paint are unique and cover every cell in the grid.Sample CaseInput:n = 2, m = 3, k = 2paint = [[1, 2], [2, 3], [2, 1], [1, 3], [2, 2], [1, 1]]Output: 5Explanation:Minute 1: Paints $(1, 2)$Minute 2: Paints $(2, 3)$Minute 3: Paints $(2, 1)$Minute 4: Paints $(1, 3)$Minute 5: Paints $(2, 2) \rightarrow$ A $2 \times 2$ square of all-black cells is now formed covering rows $1..2$ and columns $2..3$.Hence, the canvas becomes beautiful at minute 5.
Link - https://leetcode.com/discuss/post/5895561/amazon-sde-1-oa-by-anonymous_user-5i2y/
*/

// time for which k*k are painted then for all the times greater than it those blocks would also remain painted hence there is monotonicity - binary search to find that min time which gives valid O(log(n*m))
// to check if valid -> using 2d prefix sum (n*m)
// O(n*m*log(n*m)), O(n*m)
bool isValid(int middle, int n, int m, int k, vector<vector<int>>& paint) {
    vector<vector<int>> grid(n+1, vector<int>(m+1, 0));
    for (int i = 0; i < middle; i++) {
        int row = paint[i][0];
        int column = paint[i][1];
        grid[row][column] = 1;
    }

    vector<vector<int>> prefix(n+1, vector<int> (m+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            prefix[i][j] = grid[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }

    int target = k*k;
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= m; j++) {
            int subgrid_sum = prefix[i][j] - prefix[i-k][j] - prefix[i][j-k] + prefix[i-k][j-k];
            if (subgrid_sum == target) return true;
        }
    }

    return false;
}

int getMinTime(int n, int m, int k, vector<vector<int>>& paint) {
    int low = k*k, high = n*m;
    int answer = high;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (isValid(middle, n, m, k, paint)) {
            answer = middle;
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, k; cin >> n >> m >> k;
        vector<vector<int>> v(n*m, vector<int> (2));
        for (int i = 0; i < n*m; i++) {
            for (int j = 0; j < 2; j++) {
                cin >> v[i][j];
            }
        }

        cout << getMinTime(n, m, k, v) << '\n';
    }

    return 0;
}
