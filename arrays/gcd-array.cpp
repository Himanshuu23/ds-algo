/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution {
public:
    int findGCD(int a, int b) { // euclidean algorithm - O(log(min(a, b)) - time and space, O(1) space for iterative though
        if (b == 0) return a;
        return (a == 0 ? b : findGCD(b, a % b)); 
    }

    int findGCDIterative(int a, int b) {
        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    int findGCDIterative2(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    int solve(vector<int>& nums) {
        int mn = nums[0], mx = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < mn) mn = nums[i];
            if (nums[i] > mx) mx = nums[i];
        }

        return findGCD(mx, mn);
    }
};

// O(n) + O(log(min(mn,mx)))

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
