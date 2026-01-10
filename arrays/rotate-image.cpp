class Solution {
public:
    void rotate(vector<vector<int>>& v) {
        int n = v.size();
        	int start = 0, end = n-1;
	while (start < end) {
		vector<int> temp(n);
		temp = v[start];
		v[start] = v[end];
		v[end] = temp;
		start++; end--;
	}

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) swap(v[i][j], v[j][i]);


    }
};
