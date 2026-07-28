#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int i = 0;

        while (i < n) {
            if (nums[i] <= 0 || nums[i] > n) {
                i++;
                continue;
            }
            int index = nums[i] - 1;
            if (nums[i] != nums[index]) {
                swap(nums[i], nums[index]);
            } else {
                i++;
            }
        }

        for (i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }

        return n + 1;
    }
};

const int N = 1e6 + 2;

int smallestPositiveMissing(vector<int>& array, int n) {
    vector<bool> check(N, 0);

    for (int i = 0; i < n; i++) {
        if (array[i] >= 0) {
            check[array[i]] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!check[i]) {
            return i;
        }
    }

    return -1;
}

int main() {
    int n; cin >> n;

    vector<int> v;

    for (int i = 0; i < n; i++) {
        int temp = 0; cin >> temp;
        v.push_back(temp);
    }

    cout << smallestPositiveMissing(v, n) << endl;
}
