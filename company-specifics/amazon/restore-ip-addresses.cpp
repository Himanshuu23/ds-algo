#include <bits/stdc++.h>
using namespace std;

/*
You are given a string s containing only digits.Rules & DefinitionsA valid IPv4 address consists of exactly 4 octets (integers) separated by single dots (e.g., A.B.C.D).Each octet must be an integer between 0 and 255 (inclusive).No leading zeros are allowed in an octet (e.g., "0" is valid, but "01" or "001" are invalid).You cannot reorder or remove any digits from s.TaskReturn all possible valid IPv4 addresses that can be formed by inserting three dots into s. If no valid IP address can be formed, return an empty list [].ExampleInput: s = "255557"Output: ["2.55.5.57", "25.5.5.57", "25.55.5.7", "255.5.5.7"]Explanation:Each output string splits s into 4 valid octets between $0$ and $255$ without leading zeros.
String Length: $1 \le \vert{}s\vert{} \le 20$
(Note: Valid IPs can only be formed if $4 \le \vert{}s\vert{} \le 12$)
Link - https://takeuforward.org/interview-experience/amazon-interview-experience-sde-intern-set-5
*/

// since there are lot of constraints on formation of octet hence value of n (size of string) is less atmost 12
// hence using recursion + backtracking
// O(1) - time and space since tree depth (recursion tree) is fixed at 4 and max branch factor is 3
// max recursion calls <= 3^4 = 81
void backtrack(int index, int parts, const string& s, string current, vector<string>& result) {
    // base case
    if (parts == 4) {
       if (index == s.size()) {
            current.pop_back();
            result.push_back(current);
       }
       return;
    }

    // early check - if impossible to build IP from remaining string - return early
    int remaining_chars = s.size() - index;
    int remaining_parts = 4 - parts;
    if (remaining_chars < remaining_parts || remaining_chars > remaining_parts * 3) {
        return;
    }

    // take one, two or three chars in current octet
    for (int length = 1; length <= 3 && index + length <= s.size(); length++) {
        string part = s.substr(index, length);

        // discard if current part has leading zeroes
        if (length > 1 && part[0] == '0') break;

        // values must be <= 255
        int value = stoi(part);
        if (value <= 255) {
            backtrack(index + length, parts + 1, s, current + part + ".", result);
        }
    }
}

vector<string> restoreIPAddresses(string s) {
    vector<string> result;
    if (s.size() < 4 || s.size() > 12) return result;
    backtrack(0, 0, s, "", result);
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s; cin >> s;
        vector<string> result = restoreIPAddresses(s);
        for (string s : result) {
            cout << s << " ";
        }
        cout << '\n';
    }

    return 0;
}
