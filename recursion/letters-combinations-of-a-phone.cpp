#include<bits/stdc++.h>
using namespace std;

// brute force - iterative method - O(n*4^n) -> coz - taking worst case 4 lettered digit -> 9 (wxyz) ways to pair 99 would be wxyz and wxyz -> 4 * 4 = 16 = 4^2, hence if length of digit is n then ways to pair = 4 ^ n -> for each we're traversing the all n digits (copying as well) n * 4^n - space and time both
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> letters = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result = {""};

        for (char digit : digits) {
            vector<string> temporary;
            for (string current : result) {
                for (char c : letters[digit - '0']) {
                    temporary.push_back(current + c);
                }
            }
            result = temporary;
        }

        return result;
    }
};

// recursive solution -> same complexities
class Solution2 {
private:
    vector<string> letters = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
    void backtrack(int i, const string& digits, string& temporary, vector<string>& result) {
        if (i == digits.size()) {
            result.push_back(temporary);
            return;
        }

        for (char ch : letters[digits[i] - '0']) {
            temporary.push_back(ch);
            backtrack(i + 1, digits, temporary, result);
            temporary.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> result;
        string temporary;

        backtrack(0, digits, temporary, result);

        return result;
    }
};
