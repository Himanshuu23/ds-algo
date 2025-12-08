#include <bits/stdc++.h>
using namespace std;

vector<string> triangleType(int n, vector<string> w) {
    vector<string> ans;
    for (auto s : w) {
        stringstream ss(s);
        int side1, side2, side3;
        ss >> side1 >> side2 >> side3;

        if ((side1 + side2 > side3) && (side2 + side3 > side1) && (side3 + side1 > side2)) {
            if (side1 == side2 && side2 == side3) {
                ans.push_back("Equilateral");
            } else if (side1 == side2 || side2 == side3 || side3 == side1) {
                ans.push_back("Isosceles");
            } else {
                ans.push_back("None of these");
            }
        } else {
            ans.push_back("Invalid");
        }
    }

    return ans;
}

int main() {
    int n; cin >> n; cin.ignore();
    vector<string> v(n), ans(n);

    for (int i = 0; i < n; i++) {
        getline(cin, v[i]);
    };
    ans = triangleType(n, v);
    for (auto s : ans) cout << s << " ";
    cout << endl;
}
