#include<bits/stdc++.h>
using namespace std;

int reverseNumber(int n) {
    int a = 0;
    while(n > 0) {
        a = a * 10 + (n % 10);
        n /= 10;
    }

    return a;
}

int mirrorDistance(int n) {
    return abs(n - reverseNumber(n));
}

int main() {
    int n; cin >> n;
    cout << mirrorDistance(n) << endl;
}
