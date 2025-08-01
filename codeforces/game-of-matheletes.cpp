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
        int n, k, ans(0); cin >> n >> k;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(), v.end());
        int l(0), r(n-1);
        while (l < r) {
            int sum = v[l] + v[r];
            if (sum == k) {
                ans++; l++; r--;
            } else if (sum < k) l++;
            else r--;
        }
        cout << ans << endl;
    }

    return 0;
}
