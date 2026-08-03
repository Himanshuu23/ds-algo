#include<bits/stdc++.h>
using namespace std;

// recursion - O(n + N) - space and time both, n -> length of string, N -> length of output string
class Solution {
private:
    string solve(int& i, string s) {
        string result;
        int k = 0;
        while (i < s.size()) {
            char c = s[i];
            if (isdigit(c)) {
                k = k * 10 + (c - '0');
            } else if (c == '[') {
                i++;
                string subResult = solve(i, s);
                while (k--) result += subResult;
                k = 0;
            } else if (c == ']') {
                return result;
            } else {
                result += c;
            }
            i++;
        }

        return result;
    }
public:
    string decodeString(string s) {
        int i = 0;
        return solve(i, s);
    }
};

// using stacks - O(n*k_max)
class Solution2 {
public:
    string decodeString(string s) {
        string result;
        stack<char> st;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ']') st.push(s[i]);
            else {
                string substring;
                while (!st.empty() && st.top() != '[') {
                    substring += st.top();
                    st.pop();
                }
                reverse(substring.begin(), substring.end());
                st.pop();
                string digits;
                while (!st.empty() && isdigit(st.top())) {
                    digits += st.top();
                    st.pop();
                }
                reverse(digits.begin(), digits.end());
                int k = stoi(digits);
                string repeated;
                for (int i = 0; i < k; i++) repeated += substring;
                for (char c : repeated) st.push(c);
            }
        }

        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
