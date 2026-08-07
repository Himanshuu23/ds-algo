#include<bits/stdc++.h>
using namespace std;


// brute force -> linear search
// In this approach -> min would always be on right sorted array and never on left since when we rotate the array then we're moving bigger elements to the start also all elements on right sorted would be less than all elements of left sorted hence to check if we're on left or right part -> if v[middle] >= v[left] means we're still in left
class Solution {
public:
    int findMin(vector<int> &nums) {
        int start = 0, end = nums.size() - 1;
        int answer = nums[0];
        while (start <= end) {
            if (nums[start] < nums[end]) {
                answer = min(answer, nums[start]);
                break;
            }
            int middle = start + (end - start) / 2;
            answer = min(answer, nums[middle]);

            if (nums[middle] >= nums[start]) {
                start = middle + 1;
            } else {
                end = middle - 1;
            }
        }

        return answer;
    }
};
