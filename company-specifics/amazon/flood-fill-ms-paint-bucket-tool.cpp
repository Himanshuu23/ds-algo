#include <bits/stdc++.h>
using namespace std;

/*
You are given an $m \times n$ integer grid image representing an image, where image[r][c] represents the color pixel at row $r$ and column $c$. You are also given three integers: sr (start row), sc (start column), and newColor.Rules & DefinitionsTo perform a flood fill, consider the starting pixel image[sr][sc] and its original color origColor.Four-directionally connected pixels (up, down, left, right) having the same color as origColor belong to the same region.Replace the color of all pixels in this connected region with newColor.If newColor is equal to origColor, no changes are made.TaskReturn the modified image matrix after performing the flood fill operation.ExampleInput:image = [[1, 1, 1, 1, 1, 1],         [2, 0, 1, 2, 1, 1],         [3, 1, 3, 2, 0, 0]]sr = 0, sc = 2, newColor = 3Output:[[3, 3, 3, 3, 3, 3], [2, 0, 3, 2, 3, 3], [3, 1, 3, 2, 0, 0]]Explanation:The starting pixel at (0, 2) has color 1.All pixels with color 1 that are connected 4-directionally to (0, 2) are updated to 3.Pixel (2, 1) also has color 1, but it is not 4-directionally connected to the filled component, so its color remains unchanged.
Link - https://takeuforward.org/interview-experience/amazon-interview-experience-sde-intern-set-5
*/

// dfs - O(M*N), O(M*N) - space used by recursion stack in worst case
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };
void dfs(int i, int j, int m, int n, vector<vector<int>>& image, int originalColor, int newColor) {
    if (image[i][j] == newColor) return;
    image[i][j] = newColor;
    for (int k = 0; k < 4; k++) {
        int x = i + dx[k], y = j + dy[k];
        if (x >= 0 && x < m && y >= 0 && y < n && image[x][y] == originalColor) {
            dfs(x, y, m, n, image, originalColor, newColor);
        }
    }
}

void floodFill(int m, int n, vector<vector<int>>& image, int sr, int sc, int newColor) {
    dfs(sr, sc, m, n, image, image[sr][sc], newColor);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        vector<vector<int>> image(m, vector<int> (n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cin >> image[i][j];
            }
        }
        int sr, sc, newColor;
        cin >> sr >> sc >> newColor;
        floodFill(m, n, image, sr, sc, newColor);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << image[i][j] << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}
