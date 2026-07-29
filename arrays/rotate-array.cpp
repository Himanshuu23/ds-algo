#include<bits/stdc++.h>
using namespace std;

// brute force
class Solution {
public:
    void rotate(vector<int>& v, int k) {
		int n = v.size();
		k %= n;
		while (k--) {
			int first = v.back();
			for (int i = n - 1; i > 0; i--) {
				v[i] = v[i-1];
			}
			v[0] = first;
		}
    }
};

// after k rotations ith element goes to (i+k) % n position
class Solution2 {
public:
    void rotate(vector<int>& v, int k) {
        int n = v.size();
        vector<int> helper(n);
        for (int i = 0; i < n; i++) {
            helper[(i + k) % n] = v[i];
        }
        for (int i = 0; i < n; i++) {
            v[i] = helper[i];
        }
    }
};

class Solution {
public:
    void rotate(vector<int>& v, int k) {
		int n = v.size();
		k %= n;
		int count = 0;

		for (int start = 0; count < n; start++) {
			int currentIndex = start;
			int previousElement = v[start];
			do {
				int nextIndex = (currentIndex + k) % n;
				int temp = v[nextIndex];
				v[nextIndex] = previousElement;
				currentIndex = nextIndex;
				previousElement = temp;
				count++;
			} while (start != currentIndex);
		}
    }
};
