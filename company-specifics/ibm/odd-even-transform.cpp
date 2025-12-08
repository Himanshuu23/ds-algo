#include <bits/stdc++.h>
using namespace std;

// n number of times - add three to odd elements and subtract three from even elements of the array

void oddEvenTransform(int n, vector<int> &v) {
    for (int i = 0; i < n; i++) {
        for (auto &i : v)
            (i % 2 == 0) ? i -= 3 : i += 3;
    }
}

int main() {
    int n; cin >> n;
    vector<int> v(n);

    for (int i = 0; i < n; i++) cin >> v[i];
    oddEvenTransform(n, v);
    for (int i = 0; i < n; i++) cout << v[i] << " ";
    cout << endl;

    return 0;
}
