#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll power(ll a, ll b, ll m) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

ll modInverse(ll a, ll m) {
    return power(a, m-2, m);
}

int main() {
    cout << modInverse(3, 11) << endl;
    
    return 0;
}
