/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution {
public:
    int findGCD(int a, int b) {
        if (b == 0) return a;
        return (a == 0 ? b : gcd(b, a % b)); 
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
