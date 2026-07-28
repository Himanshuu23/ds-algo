class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        int i = 0, j = 0;
		string answer;
		while (i < word1.size() && j < word2.size()) {
			answer += word1[i++];
			answer += word2[j++];
		}

		while (i < word1.size()) answer += word1[i++];
		while (j < word2.size()) answer += word2[j++];

		return answer;
    }
};
