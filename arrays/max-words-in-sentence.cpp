class Solution {
public:
int numberOfWords(const string s) {
	stringstream sentence(s);
	string word;
	int ans(0);
	while (sentence >> word) ++ans;
	return ans;
}
    int mostWordsFound(vector<string>& sentences) {
        int answer = 0;
        for (auto& word : sentences) answer = max(answer, numberOfWords(word));
        return answer;
    }
};
