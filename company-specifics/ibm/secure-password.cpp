#include <bits/stdc++.h>
using namespace std;

/*

A password string, pwd consists of binary characters (0s and 1s). A cyber security expert is
trying to determine the minimum number of changes required to make the password secure. To do 
so, it must be divided into substrings of non-overlapping, even length substrings. Each substring
can only contain 1s or 0s, not a mix. This helps to ensure that the password is strong and less
vulnerable to hacking attacks.

Find the minimum number of characters that must be flipped in the password string i.e. changed
from 0 to 1 or 1 to 0 to allow the string to be divided as described.

Input: pwd = "101011"
Output: 2

Input: pwd = "100110"
Output: 3

*/

int minFlips(string s) {
    int countFlips = 0;

    for (int i = 0; i < s.size()-1; i+=2) {
        if (s[i] != s[i+1]) countFlips++;
    }

    return countFlips;
}

int main() {
    string pwd; cin >> pwd;
    int ans = minFlips(pwd);

    cout << ans << endl;

    return 0;
}
