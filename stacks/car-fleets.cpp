#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, int>> v;
        int n = position.size();
        for (int i = 0; i < n; i++) {
            v.push_back({position[i], speed[i]});
        }
        sort(v.rbegin(), v.rend());
        stack<double> st;
        for (auto& p : v) {
            double time = (double)(target - p.first) / p.second;
            if (st.empty() || st.top() < time) {
                st.push(time);
            }
        }

        return st.size();
    }
};
