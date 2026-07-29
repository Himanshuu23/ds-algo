class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.size() > s2.size()) return false;
		unordered_map<char, int> mp1, mp2;
		for (char c : s1) mp1[c]++;
		int start = 0, end = 0;
		while (end < s2.size()) {
			mp2[s2[end]]++;
			if (end - start + 1 > s1.size()) {
				mp2[s2[start]]--;
				if (mp2[s2[start]] == 0)
					mp2.erase(s2[start]);
				start++;
			}
			if (end - start + 1 == s1.size() && mp1 == mp2) return true;
			end++;
		}

		return false;
    }
};
