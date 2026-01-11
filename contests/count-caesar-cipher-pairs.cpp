#include<bits/stdc++.h>
using namespace std;

long long countPairs(vector<string>& words) {
	unordered_map<string, int> map;
	long long answer(0);

	for (auto& word : words) {
		string reference(word.length(), 'a');
		int shift = word[0] - 'a';

		for (int i = 0; i < word.length(); i++) {
			reference[i] = 'a' + (word[i] - 'a' - shift + 26) % 26;
		}

		answer += map[reference];
		map[reference]++;
	}

	return answer;
}
