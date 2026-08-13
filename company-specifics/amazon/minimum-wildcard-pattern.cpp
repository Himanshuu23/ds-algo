#include <bits/stdc++.h>
using namespace std;

/*
Given an array of strings of equal length consisting of lowercase English letters and the wildcard character '?', find a single string of the same length that matches every string in the array while containing the minimum possible number of '?' characters.Two characters at the same position match if they are equal, or if at least one of them is '?'.Input Formatarr: An array of $N$ strings of equal length $L$.Output FormatReturn a single string of length $L$ representing the optimal pattern.ExamplesExample 1:Input: arr = ["a?c", "??c", "abc"]Output: "abc"Example 2:Input: arr = ["adc", "??c", "abc"]Output: "a?c"
Link - https://leetcode.com/discuss/post/5931693/amazon-sde-6m-internship-interview-exper-qy1a/
*/

// checking characters of each word at ith position if all same we can place that same character or even if '?' then also we can do the same but if more than one distinct character then place '?'
// O(N*L), N -> total words, L -> size of each word, O(1)
string solve(vector<string>& words) {
    int n = words[0].size(), m = words.size();
    string answer(n, '?');
    for (int i = 0; i < n; i++) {
        char target = '?';
        for (int j = 0; j < m; j++) {
            if (words[j][i] == '?') continue;
            if (target == '?') {
                target = words[j][i];
            } else if (target != words[j][i]) {
                target = '?';
                break;
            }
        }
        answer[i] = target;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<string> words(n);
        for (int i = 0; i < n; i++) {
            cin >> words[i];
        }
        cout << solve(words) << '\n';
    }

    return 0;
}
