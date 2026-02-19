#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int>& height, int n) {
    if (n == 0) return 0;
    if (n == 1) return height[0];

    int left = 0, right = n-1, answer = INT_MIN;
    while (left < right) {
        answer = max(answer, min(height[right], height[left])*(right-left));
        if (height[left] < height[right]) left++;
        else right--;
    }

    return answer;
}

int main() {
    int n; cin >> n;
    vector<int> v(n);

    return 0;
}
