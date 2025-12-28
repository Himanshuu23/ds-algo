#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPalindromic(const string& s) {
        int start = 0, end = s.size() - 1;
        while (start < end) {
            if (s[start++] != s[end--]) return false;
        }

        return true;
    }

    int countSubstrings(string s) {
        int answer = 0;
        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j <= i; j++) {
                if (isPalindromic(s.substr(j, i-j+1))) answer++;
            }
        }

        return answer;
    }
};
