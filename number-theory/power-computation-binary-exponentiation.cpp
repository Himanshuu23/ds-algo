#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// computing (a^b)modm

ll modPower(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;

    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }

    return res;
}

int main() {
   cout << modPower(3, 13, 7) << endl; 
}
