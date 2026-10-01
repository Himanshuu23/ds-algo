#include<bits/stdc++.h>
using namespace std;

// O(n^2), O(1)
int bruteForce(vector<int>& height) {
    int n = height.size();
    if (n == 0 || n == 1) return 0; // single container doesn't holds any water either since width = 0
    
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int area = min(height[i], height[j]) * (j - i);
            answer = max(answer, area);
        }
    }
    return answer;
}

// using two pointers: since area depends on min(height of both ends) - we move the pointer which has less height to maximize the area - O(n), O(1)
int maximumWater(vector<int>& height) {
    int n = height.size();
    if (n == 0 || n == 1) return 0;

    int answer = 0;
    int left = 0, right = n - 1;
    while (left < right) {
        int area = min(height[left], height[right]) * (right - left);
        answer = max(answer, area);
        if (height[left] <= height[right]) left++;
        else right--;
    }
    return answer;
}
