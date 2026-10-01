#include<bits/stdc++.h>
using namespace std;

// brute force: find {absolute distance, element} for each element and after sorting take k smallest: O(nlogn), O(n)
vector<int> bruteForce(vector<int>& nums, int k, int x) {
    vector<pair<int, int>> distance;
    for (int num : nums) {
        distance.push_back({abs(num - x), num});
    }
    sort(distance.begin(), distance.end());
    vector<int> result;
    for (int i = 0; i < k; i++) {
        result.push_back(distance[i].second);
    }
    sort(result.begin(), result.end()); // since we sorted by distance not value earlier
    return result;
}

// using two pointers: trying to find the range of elements of k size - O(n-k), O(1)
vector<int> usingTwoPointers(vector<int>& nums, int k, int x) {
    int l = 0, r = nums.size() - 1;
    while (r - l >= k) { // since for valid range of k elements the difference in first and last index would be k - 1 but total elements would be k which is r - l + 1 = k (length)
        if (abs(x - nums[l]) <= abs(x - nums[r])) {
            r--;
        } else {
            l++;
        }
    }
    return vector<int> (nums.begin() + l, nums.begin() + r + 1); // we can also return upto nums.begin() + l + k - since window would have k elements
}

// using maxHeap 'k' sized so we pop largest everytime and in the end we have k smallest: O(k) space complexity for heap and the answer array and time complexity is: push and pop in heap are logh where h is size of heap and top() is O(1) so for each push and pop of n elements we have nlogk, draining the loop would be klogk since in end we would have k elements
vector<int> usingMaxHeap(vector<int>& nums, int k, int x) {
    priority_queue<pair<int, int>, vector<pair<int, int>>> pq;
    for (int num : nums) {
        pq.push({abs(num - x), num});
        if (pq.size() > k) {
            pq.pop();
        }
    }
    vector<int> answer;
    while (!pq.empty()) {
        answer.push_back(pq.top().second);
        pq.pop();
    }
    sort(answer.begin(), answer.end());
    return answer;
}

// similar approach can be used to find the start using binary search to find the start: O(log(n - k) + k), O(1) - searching n - k + 1 sized window is O(log(n-k)) while return k sized window is O(k)
vector<int> usingBinarySearch(vector<int>& nums, int k, int x) {
    int left = 0, right = nums.size() - k;
    while (left < right) {
        int middle = (left + right) / 2;
        if (abs(x - nums[middle]) > abs(x - nums[middle + k])) { // means element at middle + k is more closer to 'x' so we move towards it
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return vector<int> (nums.begin() + left, nums.begin() + left + k);
}
