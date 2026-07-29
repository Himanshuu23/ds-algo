class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int n = people.size(), left = 0, right = n - 1;
		sort(people.begin(), people.end());
		int answer = 0;
		while (left <= right) {
			if (people[left] + people[right] <= limit) {
				left++; right--;
			} else {
				right--;
			}
			++answer;
		}

		return answer;
	}
};
