/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int solve(vector<int>& p, int h) {
    int l(1), r(*max_element(p.begin(), p.end()));
    int res(r);

    while (l <= r) {
        int mid = (l+r)/2;
        int hrs(0);
        for(int n : p) hrs += (n + mid - 1)/ mid;

            if (hrs <= h) {
                res = min(res, mid);
                r = mid - 1;
            } else l = mid + 1;
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        
    }

    return 0;
}
