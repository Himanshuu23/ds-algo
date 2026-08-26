#include<bits/stdc++.h>
using namespace std;

/*
brute force: using greedy
return when can't place 
else just place character with max frequency != previous character and that previous character must not be equal to character before it so we don't have three consecutive elements
O(n*3) = O(n)
*/
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        vector<int> frequency(3);
        frequency[0] = a;
        frequency[1] = b;
        frequency[2] = c;
        string answer = "";
        char previous1 = '#';
        char previous2 = '#';
        long long n = a * b * c;
        while (true) {
            int best = -1;
            for (int i = 0; i < 3; i++) {
                if (frequency[i] > 0 && (i + 'a' != previous1 || previous1 != previous2)) {
                    if (best == -1 || frequency[i] > frequency[best]) {
                        best = i;
                    }
                }
            }

            if (best == -1) {
                break;
            }

            answer += best + 'a';
            frequency[best]--;
            previous2 = previous1;
            previous1 = best + 'a';
        }

        return answer;
    }
};

/*
optimization: use maxHeap to get the max element in log(3) - O(nlog(3)) = O(n) 
*/
class Solution2 {
public:
    string longestDiverseString(int a, int b, int c) {
        vector<int> frequency(3, 0);
        frequency[0] = a;
        frequency[1] = b;
        frequency[2] = c;

        priority_queue<pair<int, int>> pq;

        for (int i = 0; i < 3; i++) {
            if (frequency[i] > 0) {
                pq.push({ frequency[i], i});
            }
        }

        string answer = "";
        char previous1 = '#';
        char previous2 = '#';

        while (!pq.empty()) {
            auto [freq, character] = pq.top();
            pq.pop();

            if (character + 'a' == previous1 && previous1 == previous2) {
                if (pq.empty()) {
                    return answer;
                } else {
                    auto [new_freq, new_character] = pq.top();
                    pq.pop();

                    pq.push({ freq, character });
                    freq = new_freq;
                    character = new_character;
                }
            }

            answer += character + 'a';
            previous2 = previous1;
            previous1 = character + 'a';
            if (freq > 1) {
                pq.push({ --freq, character });
            }
        }

        return answer;
    }
};
