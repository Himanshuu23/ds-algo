/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class SegmentTree {
    vector<long long> array, tree;
    int n;

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = start;
            return;
        }
        int middle = (start + end) / 2;
        build(2*node, start, middle);
        build(2*node+1, middle + 1, end);
        int left = tree[2*node];
        int right = tree[2*node+1];
        tree[node] = (array[left] <= array[right]) ? left : right;
    }

    int query(int node, int start, int end, int left, int right) {
        if (right < start || left > end) return -1;
        if (left <= start && end <= right) return tree[node];
        int middle = (start + end) / 2;
        int l = query(2*node, start, middle, left, right);
        int r = query(2*node+1, middle + 1, end, left, right);
        if (l == -1) return r;
        if (r == -1) return l;
        return (array[l] <= array[r]) ? l : r;
    }

    public:
    SegmentTree(vector<long long>& input) {
        n = input.size();
        array = input;
        tree.assign(4*n, 0);
        build(1, 0, n - 1);
    }

    int query(int left, int right) {
        return query(1, 0, n - 1, left, right); 
    }
};

// O(nlogn), O(n) - space
long long solve(int l, int r, vector<long long>& v, SegmentTree& sg) {
    if (l > r) return 0;
    if (l == r) return v[l];

    int minIndex = sg.query(l, r);
    long long area = 1LL * v[minIndex] * (r - l + 1);
    return max({ area, solve(l, minIndex-1, v, sg), solve(minIndex+1, r, v, sg) });
}

long long largestRectangle(vector<long long>& v) {
    SegmentTree sg(v);
    return solve(0, v.size() - 1, v, sg);
}

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
