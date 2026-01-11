#include<bits/stdc++.h>
using namespace std;

int residuePrefixes(const string& s) {
	int answer(0);
	unordered_map<char, int> map(26);
	for (int i = 0; i < s.size(); i++) {
		map[s[i]]++;
		if (map.size() == (i+1)%3) answer++;
	}

	return answer;
}
