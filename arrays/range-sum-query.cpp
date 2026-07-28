class NumMatrix {
private:
	vector<vector<int>> prefix;
public:
    NumMatrix(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size();
		prefix = vector<vector<int>> (n+1, vector<int> (m+1, 0));
       
		for (int i = 0; i < n; i++) {
			int s = 0;
			for (int j = 0; j < m; j++) {
				s += matrix[i][j];
				int above = prefix[i][j+1];
				prefix[i+1][j+1] = above + s;
			}
		}

    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
		row1++; col1++; row2++; col2++;
		return prefix[row2][col2] - prefix[row2][col1-1] - prefix[row1-1][col2] + prefix[row1-1][col1-1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
