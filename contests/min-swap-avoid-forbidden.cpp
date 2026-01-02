#include<bits/stdc++.h>
using namespace std;

int minSwaps(vector<int>& nums, vector<int>& forbidden) {
    int count(0), n = nums.size(), maxIndex(0);
    map<int, int> num_map, frequency_map, matching_map;

    for (int i = 0; i < n; i++) {
        int value = nums[i];
        if (value == forbidden[i]) {
            count++;
            matching_map[value]++;
            maxIndex = max(maxIndex, matching_map[value]);
        }
        num_map[value]++; frequency_map[forbidden[i]]++;
    }

    for (auto& p : num_map) {
        if (p.second > n - frequency_map[p.first]) return -1;
    }

    return max(maxIndex, (count+1)/2);
}
