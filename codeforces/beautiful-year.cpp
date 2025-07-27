/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool distinct(int n) {
    string s = to_string(n);
    set<char> st(s.begin(), s.end());
    return s.length() == st.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        int n; cin >> n;
        n++;
        while (true) {
            if (distinct(n)) {
                cout << n << endl;
                break;
            } else n++;
        }

    return 0;
}
