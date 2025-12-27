#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPlace(vector<int>& position, int balls, int force) {
        int count = 1, last = position[0];
        for (auto p : position) {
            if (p - last >= force) {
                ++count;
                last = p;
            }
        }

        return count >= balls;
    }

    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        int start = 0, end = position.back() - position[0], answer = 0;

        while (start <= end) {
            int middle = (start + end) / 2;
            if (canPlace(position, m, middle)) {
                answer = middle;
                start = middle + 1;
            } else end = middle - 1;
        }

        return answer;        
    }
};
