/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    int trap(vector<int>& height) {
		int l = 0, r = height.size() - 1;
		int leftMax = height[l], rightMax = height[r];
		int answer = 0;
		while (l < r) {
			if (leftMax < rightMax) {
				l++;
				leftMax = max(leftMax, height[l]);
				answer += leftMax - height[l];
			} else {
				r--;
				rightMax = max(rightMax, height[r]);
				answer += rightMax - height[r];
			}
		}

		return answer;
    }
};
