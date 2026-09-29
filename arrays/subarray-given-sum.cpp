#include <bits/stdc++.h>
using namespace std;

// brute force: trying all possible subarray and checking any of them has sum = given_sum - O(n^3), O(1)
pair<int, int> bruteForce(vector<int>& v, int s) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += v[k];
            }
            if (sum == s) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// using running prefix sum: O(n^2), O(1) - removing the third loop - fix the starting position 'i' and keep adding new element using another loop - extending the array from 'i'
pair<int, int> usingRunningPrefixSum(vector<int>& v, int s) {
    int n = v.size();
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += v[j];
            if (sum == s) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// using sliding window: O(n), O(1) - works only for non-negative elements (not for negative numbers)
pair<int, int> usingSlidingWindow(vector<int>& v, int s) {
    int left = 0, right = 0, sum = 0;
    while (right < v.size()) {
        sum += v[right];
        while (sum > s && left <= right) {
            sum -= v[left];
            left++;
        }
        if (sum == s) {
            return {left, right};
        }
        right++;
    }
    return {-1, -1};
}

/*
If prefix[j] - prefix[i] = sum, then the subarray from i+1 to j sums to sum.
So we store prefix sums in a hash map as we go.

Approach - hash maps + prefix sum
*/

pair<int, int> subarraySum(vector<int>& arr, int n, int sum) {
    unordered_map<int, int> mp;
    int prefix = 0;

    for (int i = 0; i < n; i++) {
        prefix += arr[i];

        if (prefix == sum) {
            return { 0, i };
        }

        if (mp.count(prefix - sum)) {
            return { mp[prefix - sum] + 1, i }; 
        }

        mp[prefix] = i;
    }

    return { -1, -1 };
}

int main() {
    int n, sum; cin >> n >> sum;
    vector<int> array;

    for (int i = 0; i < n; i++) {
        int temp = 0; cin >> temp;
        array.push_back(temp);
    }

    pair<int, int> ans = subarraySum(array, array.size(), sum);

    if ((ans.first != -1) && (ans.second != -1)) {
        cout << ans.first << " " << ans.second << endl;
    } else {
        cout << "No such pair was found" << endl;
    }

    return 0;
}
