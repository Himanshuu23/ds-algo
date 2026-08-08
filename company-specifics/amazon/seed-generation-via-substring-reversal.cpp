#include <bits/stdc++.h>
using namespace std;

/*
Problem StatementAmazon is developing a new hashing approach that generates a seed number from an input string $s$.Given a string $s$ and an integer $k$, find the number of distinct starting positions for a substring of length $k$ such that reversing that substring results in a new string that is strictly lexicographically smaller than the original string $s$.Constraints$2 \le \vert{}s\vert{} \le 10^6$$1 \le k \le \min(\vert{}s\vert{}, 20)$Sample CaseInput$s = \text{"amazon"}$$k = 3$
Analysis of Substrings of Length 3Index 0..2 ("ama"): Reversing gives "amazon" $\rightarrow$ Equal (Not strictly smaller)Index 1..3 ("maz"): Reversing gives "azamon" $\rightarrow$ "azamon" > "amazon" (Larger)Index 2..4 ("azo"): Reversing gives "amozan" $\rightarrow$ "amozan" > "amazon" (Larger)Index 3..5 ("zon"): Reversing gives "amanoz" $\rightarrow$ "amanoz" < "amazon" (Smaller!)Output
Link : https://leetcode.com/discuss/post/4660709/amazon-oa-recent-questions-sharing-for-t-8ze5/
*/

// brute force - checking each k sized substring and if it is lexicographically greater than its reverse then +1 else no 
// this works coz n is 10 power 6 and k is atmost 20 so (nk) = 10 power 7 and we can have 10 power 7 in less than 0.05 secs
// O(nk), O(k)
int solve1(string& s, int k) {
	int n = s.size(), answer = 0;
	for (int i = 0; i <= n - k; i++) {
		string substring = s.substr(i, k);
		string reversed_substring = substring;
		reverse(reversed_substring.begin(), reversed_substring.end());
		if (reversed_substring < substring) ++answer;
	}

	return answer;
}

// we can remove O(k) space using two pointers - O(nk), O(1)
int solve2(string& s, int k) {
	int n = s.size(), answer = 0;
	for (int i = 0; i <= n - k; i++) {
		int left = i, right = i + k - 1;
		while (left < right) {
			if (s[left] > s[right]) {
				++answer;
				break;
			} else if (s[left] < s[right]) {
				break;
			}
			left++; right--;
		}
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
		int k; cin >> k;
		cout << solve1(s, k) << '\n';
		cout << solve2(s, k) << '\n';
    }

    return 0;
}
