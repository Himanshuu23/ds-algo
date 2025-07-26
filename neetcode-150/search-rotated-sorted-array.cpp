/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(vector<int>& v, int t) {
    int l(0), r(v.size()-1);

    while (l <= r) {
        int mid = (l + r) / 2;
        if (v[mid] == t) return mid;
        else if (v[l] <= v[mid]) {
            if ((t >= v[l]) && (t < v[mid])) r = mid - 1;
            else l = mid + 1;
        } else {
            if ((t > v[mid]) && (t <= v[r])) l = mid + 1;
            else r = mid - 1;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        int n, t; cin >> n >> t;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        cout << solve(v, t) << endl;
    }

    return 0;
}
