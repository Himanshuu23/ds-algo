class Solution {
public:
    vector<int> majorityElement(vector<int>& v) {
		int n = v.size();
        unordered_map<int, int> count;
		for (int i = 0; i < n; i++) {
			count[v[i]]++;
		}

		vector<int> answer;
		for (auto& [key, value] : count) {
			if (value > n/3) answer.push_back(key);
		}

		return answer;

    }
};

class Solution {
public:
    vector<int> majorityElement(vector<int>& v) {
		int n = v.size();
       	int num1 = -1, num2 = -1, count1 = 0, count2 = 0;
		for (int num : v) {
			if (num == num1) count1++;
			else if (num == num2) count2++;
			if (count1 == 0) {
				num1 = num;
				count1 = 1;
			} else if (count2 == 0) {
				num2 = num;
				count2 = 1;
			} else count1--, count2--;
		}

		count1 = 0, count2 = 0;
		for (int x : v) {
			if (x == num1) count1++;
			if (x == num2) count2++;
		}

		vector<int> answer;
		if (count1 > n/3) answer.push_back(num1);
		if (count2 > n/3 && num1 != num2) answer.push_back(num2);

		return answer;
    }
};
