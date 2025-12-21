#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll extendedGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    ll x1, y1;
    ll gcd = extendedGCD(b, a%b, x1, y1);
    x = y1; // so coefficient of (a%b) becomes a
    y = x1 - (a / b) * y1; // using a%b = a - (a/b)*b
    return gcd;
}

ll modInverse(ll a, ll m) {
    ll x, y;
    ll gcd = extendedGCD(a, m, x, y);
    if (gcd != 1) return -1; // inverse won't exist
    return (x % m + m) % m; // making +ve
}

int main() {
    cout << modInverse(3, 11) << endl;
    cout << modInverse(6, 9) << endl;

    return 0;
}
