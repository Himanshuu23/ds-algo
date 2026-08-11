#include<bits/stdc++.h>
using namespace std;

// amazon OA problem
class Solution {
public:
    int totalStrength(vector<int>& power) {
        int n = power.size();
            long long MOD = 1e9 + 7;
    
    // building prefix sum (1 based) not 0 based coz then prefix sum is p[r]-p[l-1] hence for first element l-1 is negative so we require extra check but here just p[r+1]-p[l]
    vector<long long> P(n+1, 0);
    for (int i = 0; i < n; i++) {
        P[i+1] = (P[i] + power[i]) % MOD;
    }

    vector<long long> PP(n+2, 0);
    for (int i = 0; i <= n; i++) {
        PP[i+1] = (PP[i] + P[i]) % MOD;
    }

    vector<int> left_bound(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && power[st.top()] >= power[i]) {
            st.pop();
        }
        if (!st.empty()) left_bound[i] = st.top();
        st.push(i);
    }

    vector<int> right_bound(n, n);
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && power[st.top()] > power[i]) {
            st.pop();
        }
        if (!st.empty()) right_bound[i] = st.top();
        st.push(i);
    }

    long long total_power = 0;
    for (int i = 0; i < n; i++) {
        int L = left_bound[i];
        int R = right_bound[i];

        long long left_count = i - L;
        long long right_count = R - i;
        
        // since to find sum of subarrays in (0, i) using pp[i] we do pp[i] just that but since lower bound and upper bound array store 0 based indexing wew would have done pp[i+1] and so we're using the same for [l, r] range pp[r+1] - pp[l+1]
        long long right_sum = (PP[R+1] - PP[i+1] + MOD) % MOD;
        long long left_sum = (PP[i+1] - PP[L+1] + MOD) % MOD;

        long long subarray_sum = (right_sum * left_count % MOD - left_sum * right_count % MOD + MOD) % MOD;
        
        long long contribution = (subarray_sum * power[i]) % MOD;
        total_power = (total_power + contribution) % MOD;
    }

    return total_power;
    }
};
