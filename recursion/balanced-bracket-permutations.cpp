#include<bits/stdc++.h>
using namespace std;

// Time Complexity: valid sequence can be split as: ( A ) B. Now if A contains i pairs, then B would have n - i - 1 pairs. So number of solutions Cn => i=0∑n−1CiCn−i−1 (first sum from 0 to n - 1, Ci and Cn-i-1 -> combination of all possible pairs. This is exactly cataln numbers which is Cn = (1/n+1)C(2n, n) = (2n!)/(n+1)!n! = (4^n)/n^(3/2)) Now if we have 2n characters we have to spend O(n) time per output. So overall complexity: O(4^n/square_root(n)), space O(n)
class Solution {
    void generate(int open, int close, string& s, vector<string>& result) {
        if (open == 0 && close == 0) { // valid sequency built
            result.push_back(s);
            return;
        }

        if (close == 0) return; // we can't build anything valid with remaining opening brackets

        if (open == close) {
            string current = s;
            current.push_back('(');
            generate(open - 1, close, current, result);
        }

        else if (open == 0) {
            string current = s;
            current.push_back(')');
            generate(open, close - 1, current, result);
        }

        else {
            string current1 = s, current2 = s;
            current1.push_back('(');
            current2.push_back(')');
            generate(open - 1, close, current1, result);
            generate(open, close - 1, current2, result);
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string s;
        generate(n, n, s, result);
        return result;
    }
};

// From above: answer is of format ( A ) B means we can also using dynamic programming to try all possible pairs that way - and make splits for each left and right -> ( left ) right where left and right are valid pairs lengths of varying length.
// dp[0] => valid answers for 0 pairs
// total splits we can make 1 to n - 1, we try all possible pairs we can use 0 pairs to n pairs and build answer for each split 1 to n - 1
// if left has i pairs for kth split then remaining pairs are k - i but we have extra pair around left -> ( left ) means right would have k - i - 1
// suppose for n = 3, dp[0] = [""] empty string -> BASE CASE - one way to build that is nothing
// dp[1] = [ "()" ], dp[2] = ["()()", "(())"] for dp[3] we can reuse for splits like i = 0 we get left = dp[0] -> left gets nothing dp[0] pre calculated and dp[2] is given to right
// Complexity same as above
class Solution3 {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> result(n+1);
        result[0] = {""};

        for (int k = 0; k <= n; k++) { // we can also start with k = 1 coz k = 0 means no pairs we have already calculated that it doesn't even runs
            for (int i = 0; i < k; i++) {
                for (const string& left : result[i]) {
                    for (const string& right : result[k-i-1]) {
                        result[k].push_back("(" + left + ")" + right);
                    }
                }
            }
        }

        return result[n];
    }
};
