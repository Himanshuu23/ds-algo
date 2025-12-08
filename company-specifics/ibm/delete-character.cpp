#include <bits/stdc++.h>
using namespace std;

/*
 
 The students are provided with a string that consists of lowercase English letters. In one
 move, they can choose any one index i, and let the character at that index be c. Then, the
 first occurence of c to the left of i, and the first occurence of c to the right of i are
 deleted (Note: the operation can still be carried out even if either the left or right 
 occurence doesn't exist). For example, if word = "adabacaea", and if index 4 is chosen (0-based),
 the first occurence of 'a' to the left and right of index 4 (indices 2 and 6) are deleted
 leaving word = "adbacea".

 Find the minimum number of moves the students need to perform in order to get a word of 
 minimal length.

 Input: word = "baabacaa"
 Output: 3

 Explanation: "baabacaa" -> "baaacaa" -> "bacaa" -> "bca"

 */

int findMinimumMoves(string word) {
    unordered_map<char, int> countChars;
    for (char c : word) countChars[c]++;

    int minMoves = 0;
    for (auto &[ch, count] : countChars) minMoves += count / 2;

    return minMoves;
}

int main() {
    string word; cin >> word;
    int ans = findMinimumMoves(word);

    cout << ans << endl;

    return 0;
}
