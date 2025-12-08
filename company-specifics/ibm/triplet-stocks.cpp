#include <bits/stdc++.h>
using namespace std;

/*
 
The cost of a stock on each day is given in an array, arr. An investor wants to buy the stocks
in triplets such that the sum of the cost for three days is divisble by d. The goal is to find
the number of district triplets (i, j, k) such that i < j < k and the sum (a[i] + a[j] + a[k])
is divisble by d.

arr = [3, 3, 4, 7, 8], d = 5
- indices (0, 1, 2), (0, 2, 4), (1, 2, 3)
Output = 3

*/

int findTriplets(int n, int d, vector<int> v) {
    int ans(0);
    for (int i = 0; i < n-2; i++) {
        for (int j = i+1; j < n-1; j++) {
            for (int k = j+1; k < n; k++) {
                if ((v[i]+v[j]+v[k])%d == 0) ans++;
            } 
        }
    }

    return ans;
}

int main() {
    int n, d; cin >> n >> d;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    int ans = findTriplets(n, d, v);

    cout << ans << endl;
    
    return 0;
}
