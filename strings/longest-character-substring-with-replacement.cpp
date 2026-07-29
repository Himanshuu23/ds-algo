class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> mp;
		int left = 0, right = 0, answer = 0, maxFrequency = 0;
		while (right < s.size()) {
			mp[s[right]]++;
			maxFrequency = max(maxFrequency, mp[s[right]]);
			while ((right - left + 1) - maxFrequency > k) {
				mp[s[left]]--;
				if (mp.count(s[left]) == 0)
					mp.erase(s[left]);
				left++;
			}
			answer = max(answer, right - left + 1);
			right++;
		}

		return answer;
    }
};
