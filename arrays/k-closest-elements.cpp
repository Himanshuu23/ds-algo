#include<bits/stdc++.h>
using namespace std;

// using two pointers
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int l = 0, r = arr.size() - 1;
		while (r - l >= k) {
			if (abs(x - arr[l]) <= abs(x - arr[r])) {
				r--;
			} else {
				l++;
			}
		}

		return vector<int>(arr.begin() + l, arr.begin() + r + 1);
    }
};

// using maxHeap
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        priority_queue<pair<int, int>, vector<pair<int, int>>> pq;
		for (int num : arr) {
			pq.push({abs(x - num), num});
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
};

// using binary search
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
		int left = 0, right = arr.size() - k;
		while (left < right) {
			int middle = (left + right) / 2;
			if (abs(x - arr[middle]) > abs(x - arr[middle + k])) {
				left = middle + 1;
			} else {
				right = middle;
			}
		}
		return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};
