class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		unordered_set<char> window;
		int left = 0, right = 0, answer = 0;
		while (right < s.size()) {
			if (window.count(s[right]) == 0) {
				window.insert(s[right]);
				answer = max(answer, right - left + 1);
			} else {
				while (window.count(s[right])) {
					window.erase(s[left]);
					left++;
				}
				window.insert(s[right]);
			}
			right++;
		}

		return answer;
    }
};
