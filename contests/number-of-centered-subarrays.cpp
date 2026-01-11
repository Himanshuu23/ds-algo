#include<bits/stdc++.h>
using namespace std;

int centeredSubarrays(vector<int>& v) {
	int n = v.size(), answer(0);
	for (int i = 0; i < n; i++) {
		unordered_set<int> set;
		for (int j = i, sum = 0; j < n; j++) {
			set.insert(v[j]);
			sum += v[j];
			if (set.find(sum) != set.end()) ++answer;
		}
	}

	return answer;
}
