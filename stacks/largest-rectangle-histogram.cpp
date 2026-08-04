/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// O(n2) time and O(1) space
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int answer = 0, n = heights.size();
        for (int i = 0; i < n; i++) {
            int height = heights[i];

            int right = i + 1;
            while (right < n && heights[right] >= height) right++;
            int left = i - 1;
            while (left >= 0 && heights[left] >= height) left--;
            right--;
            left++;
            answer = max(answer, height*(right - left + 1));
        }

        return answer;
    }
};

int solve(vector<int>& heights, int n) { // for each ith index finding all area from prev max than ith element till smaller than ith element but no including that in the window
    stack<int> st;
    int area(0);
    for (int i = 0; i <= n; i++) {
        int curr = (i == n) ? 0 : heights[i];
        while (!st.empty() && heights[st.top()] >= curr) {
            int h = heights[st.top()]; st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            area = max(area, h * w);
        }
        st.push(i);
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int>v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(v, n) << endl;
    }

    return 0;
}
