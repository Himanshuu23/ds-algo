#include <bits/stdc++.h>
using namespace std;

/*
Given an array of $n$ strings strings, where each string has a length of $L$, count the number of pairs $(i, j)$ with $0 \le i < j < n$ such that strings[i] and strings[j] are considered similar.Two strings are defined as similar if:They are identical, ORThey can be made identical by swapping/modifying at most one position (or matching a common key/canonical pattern depending on the exact variant).TaskReturn the total number of similar string pairs as a long long.Constraints$1 \le n \le 10^5$$1 \le L \le 20$All strings consist of lowercase English letters.
Link - https://leetcode.com/discuss/post/2180363/amazon-oa-by-anonymous_user-xrnn/
*/

// Brute Force ($O(N^2 \cdot L)$): Comparing every pair $(i, j)$ takes $\frac{N(N-1)}{2}$ comparisons of length $L$. For $N = 10^5$, $N^2 \approx 10^{10}$ operations $\rightarrow$ TLE.
// Using Hashmaps - make wild cards like abc -> *bc, a*c, ab* and suppose abz would also make ab* so it would increase answer by mp[ab*] since there might be many other strings who made that -> O(N*L), O(N*L)
long long solve(vector<string>& words) {
    unordered_map<string, int> mp;
    unordered_map<string, int> exact_mp;
    long long answer = 0; 
    for (string word : words) {
        int L = word.size();
        for (int i = 0; i < L; i++) {
            string wildcard = word;
            wildcard[i] = '*';
            answer += mp[wildcard];
            mp[wildcard]++;
        }
        // if exactly same element then add extra that is for abc, abc we add all 3 wildcards although just one must be added
        answer -= exact_mp[word]*(L-1);
        exact_mp[word]++;
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
