#include <bits/stdc++.h>
using namespace std;

/*
Given a string str consisting of lowercase and/or uppercase English alphabets, find the length of the smallest substring that contains all the distinct characters present in the entire string str.Input Formatstr: A string of length $N$.Output FormatReturn an integer representing the length of the shortest substring containing all distinct characters of str.ExamplesExample 1:Input: str = "AABBBCBBAC"Total Distinct Characters: 3 ('A', 'B', 'C')Output: 3Explanation: Substrings "BAC" or "CBA" have length 3 and contain all 3 distinct characters.Example 2:Input: str = "aaab"Total Distinct Characters: 2 ('a', 'b')Output: 2Explanation: Substring "ab" has length 2 and contains both 'a' and 'b'.Example 3:Input: str = "GEEKSGEEKS"Total Distinct Characters: 4 ('G', 'E', 'K', 'S')Output: 5Explanation: Substring "KSGEE" or "EKSGE" has length 5 and contains all 4 distinct characters.
Link - https://www.geeksforgeeks.org/interview-experiences/amazon-interview-experience-6-months-intern-for-sde-1/
*/

// sliding window + frequency array (256) - 256 possible ascii chars, using hashmaps - collision might cause another O(N) while erase
// O(N), O(1)
int getSmallestDistantWindow(const string s) {
    int n = s.size();
    if (n == 0) return 0;

    int total_distincts = 0;
    vector<bool> visited(256, false);
    for (char c : s) {
        if (!visited[(unsigned char)c]) {
            visited[(unsigned char)c] = true;
            total_distincts++;
        }
    }
    
    vector<int> frequency(256, 0);
    int start = 0, end = 0, answer = n, count = 0;
    while (end < n) {
        if (frequency[(unsigned char)s[end]] == 0) { // found new char
            count++;
        }
        frequency[(unsigned char)s[end]]++;

        while (count == total_distincts) {
            answer = min(answer, end - start + 1);
            frequency[(unsigned char)s[start]]--;
            if (frequency[(unsigned char)s[start]] == 0) {
                count--;
            }
            start++;
        }
        end++;
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s; cin >> s;
        cout << getSmallestDistantWindow(s) << '\n';
    }

    return 0;
}
