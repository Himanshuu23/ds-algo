class Solution {
public:
void solve(int n, vector<int>& v, int start, int end) {
    if (start >= end) return;
    
    int mid = (start + end) / 2;
    solve(n, v, start, mid);
    solve(n, v, mid + 1, end);

    vector<int> temp;
    int i = start, j = mid + 1;
    
    while (i <= mid && j <= end) {
        if (v[i] <= v[j]) temp.push_back(v[i++]);
        else temp.push_back(v[j++]);
    }

    while (i <= mid) temp.push_back(v[i++]);
    while (j <= end) temp.push_back(v[j++]);

    for (int k = 0; k < temp.size(); k++) v[start + k] = temp[k];
}
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        solve(n, nums, 0, n-1);
        return nums;
    }
};
