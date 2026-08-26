#include<bits/stdc++.h>
using namespace std;

// base case: answer cannot exist if any character is present > n/2 times where n is the size of the string -> return ""
/*
brute force: Using greedy
just place one char of most frequent char and then something different and keep decreasing and when count is zero obv remove them from frequency map - o(n*26) = O(n), O(26) = O(1) for space
*/
class Solution {
public:
    string reorganizeString(string s) {
        int n = s.size();
        vector<int> frequency(26, 0);

        for (char c : s) {
            frequency[c - 'a']++;
        }

        string answer = "";
        char previous = '#';

        for (int i = 0; i < n; i++) {
            int best = -1;
            
            for (int j = 0; j < 26; j++) {
                if (frequency[j] > 0 && 'a' + j != previous) {
                    if (best == -1 || frequency[j] > frequency[best]) {
                        best = j;
                    }
                }
            }

            if (best == -1) {
                return "";
            }

            answer += 'a' + best;
            frequency[best]--;
            previous = 'a' + best;
        }

        return answer;
    }
};

/*
Optimization: just use maxheap to get the next max character that is not same as previous - O(nlog(26)) = O(n)
*/
class Solution2 {
public:
    string reorganizeString(string s) {
        int n = s.size();

        vector<int> frequency(26, 0);

        for (char c : s) {
            frequency[c - 'a']++;
        }

        priority_queue<pair<int, int>> pq;

        for (int i = 0; i < 26; i++) {
            if (frequency[i] > 0) {
                pq.push({ frequency[i], i });
            }
        }

        string answer = "";
        char last_placed = '#';

        for (int i = 0; i < n; i++) {
            auto [freq, character] = pq.top();
            pq.pop();
            if (character + 'a' == last_placed) {
                if (pq.empty()) {
                    return "";
                }
                auto [new_freq, new_character] = pq.top();
                pq.pop();
                pq.push({ freq, character });
                freq = new_freq;
                character = new_character;
            }
            answer += character + 'a';
            last_placed = character + 'a';
            if (freq > 1) pq.push({ --freq, character });
        }

        return answer;
    }
};
