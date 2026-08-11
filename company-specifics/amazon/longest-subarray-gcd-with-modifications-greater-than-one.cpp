#include <bits/stdc++.h>
using namespace std;

/*
You are given an array of integers nums and an integer maxChangeTimes.Rules & DefinitionsYou can change at most maxChangeTimes elements in the array to any positive integer of your choice.A subarray is defined as a contiguous non-empty sequence of elements.The Greatest Common Divisor (GCD) of the modified subarray must be strictly greater than 1 ($\text{GCD} > 1$).TaskFind the maximum length of a contiguous subarray such that all elements in that subarray can share a common divisor $d > 1$ after performing at most maxChangeTimes element replacements.ExampleInput: nums = [1, 3, 5, 4], maxChangeTimes = 1Output: 2Explanation:Option 1: Consider target prime $p = 3$. Look at subarray [1, 3] (length 2). We change 1 to 3 ($1$ change used). Array becomes [3, 3], where $\text{GCD}(3, 3) = 3 > 1$.Option 2: Consider target prime $p = 2$. Look at subarray [5, 4] (length 2). We change 5 to 4 ($1$ change used). Array becomes [4, 4], where $\text{GCD}(4, 4) = 4 > 1$.The maximum achievable valid subarray length is 2.
Link - https://www.reddit.com/r/leetcode/comments/1lz8kgv/bombed_amazon_oa/
*/

// insert all distinct primes in array into a set and check longest window with atmost 'k' non divisble elements by each of p - using sliding window
// O(np), O(p), p -> total distinct prime factors in array
int maximumSubarrayGCD(vector<int>& v, int maxChangeTimes) {
    int n = v.size();

    unordered_set<int> s; // all prime factors possible
    for (int x : v) {
        int temp = x;
        for (int d = 2; d * d <= temp; d++) {
            if (temp % d == 0) {
                s.insert(d);
                while (temp % d == 0) temp /= d; // so suppose if d is 4 it can never be answer since 2 came earlier
            }
        }
        if (temp > 1) s.insert(temp); // means remaining temp also prime
    }

    int answer = min(n, maxChangeTimes + 1);
    for (int p : s) {
        int start = 0, end = 0, distincts = 0;
        while (end < n) {
            if (v[end] % p != 0) distincts++;
            while (distincts > maxChangeTimes) {
                if (v[start] % p != 0) {
                    distincts--;
                }
                start++;
            }
            answer = max(answer, end - start + 1); 
            end++;
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        int maxChangeTimes; cin >> maxChangeTimes;
        cout << maximumSubarrayGCD(v, maxChangeTimes) << '\n';
    }

    return 0;
}
