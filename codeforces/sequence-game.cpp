/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n;
    cin >> t;

    while (t--) {
        cin >> n;
        vector<int> a, b;

        for (int i = 0; i < n; i++) {
            int temp = 0; cin >> temp;
            b.push_back(temp);
        }

        a.push_back(b[0]);
        for (int i = 1; i < n; i++) {
            if (b[i] >= b[i-1]) a.push_back(b[i]);
            
            else {
                a.push_back(1);
                a.push_back(b[i]);
            }
        }

        cout << a.size() << endl;
        for (auto it: a) {
            cout << it << " ";
        }
        cout << endl;
    }

    return 0;
}
