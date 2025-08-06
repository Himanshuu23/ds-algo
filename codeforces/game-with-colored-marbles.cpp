/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n; cin >> n;
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            int temp; cin >> temp;
            mp[temp]++;
        }
        ll u(0), k(0);
        for (auto& [key, val] : mp) {
            if (val == 1) u++;
            else k++;
        }
        
        cout << ((u+1)/2)*2 + k << endl;
    }

    return 0;
}
