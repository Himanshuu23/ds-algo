#include<bits/stdc++.h>
using namespace std;

// using sorting - O(m * nlogm), O(m*n) -> where m -> number of words, n -> average length of each word
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> dictionary;

        for (int i = 0; i < 26; i++) {
            dictionary[order[i]] = i;
        }

        auto compare = [&](const string& a, const string& b) {
            for (int i = 0; i < min(a.size(), b.size()); i++) {
                if (a[i] != b[i]) {
                    return dictionary[a[i]] < dictionary[b[i]];
                }
            }

            return a.size() < b.size();
        };

        return is_sorted(words.begin(), words.end(), compare);
    }
};

// O(m*n), O(1) 
class Solution2 {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> dictionary;

        for (int i = 0; i < order.size(); i++) {
            dictionary[order[i]] = i;
        }

        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i+1];
            int j = 0;

            for (; j < w1.size(); j++) {
                if (j == w2.size()) return false; // previous word has larger length than next word
                if (w1[j] != w2[j]) {
                    if (dictionary[w1[j]] > dictionary[w2[j]]) {
                        return false;
                    }
                    break; // prev word smaller than next -> move to next pair
                }
            }
        }

        return true;
    }
};
