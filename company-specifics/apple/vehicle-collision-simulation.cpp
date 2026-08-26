#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement
An array of integers vehicles represents vehicles on a single-lane road.
The absolute value represents the size/weight of the vehicle, while the sign specifies direction (positive for right/east, negative for left/west).
All vehicles move at equal speeds. When two vehicles moving in opposite directions meet:
The larger vehicle survives and continues.
If both are equal size, both are destroyed.
Vehicles moving in the same direction never collide.
Return the remaining vehicles in order.
*/

// asteroid collision - O(n), O(n)
vector<int> vehicleCollision(vector<int>& vehicles) {
    vector<int> st;
    for (int v : vehicles) {
        while (!st.empty() && v < 0 && st.back() > 0) {
            int difference = v + st.back();

            if (difference < 0) {
                st.pop_back(); 
            } else if (difference > 0) {
                v = 0;
            } else {
                v = 0;
                st.pop_back();
            }
        }
        if (v != 0) {
            st.push_back(v);
        }
    }
    
    return st;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
