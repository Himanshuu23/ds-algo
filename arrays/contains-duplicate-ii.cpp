class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_set<int> window;
		int left = 0, right = 0;
		while (right < nums.size()) {
			if (right - left > k) {
				window.erase(nums[left]);
				left++;
			}
			if (window.find(nums[right]) != window.end()) return true;
			window.insert(nums[right]);
			right++;
		}

		return false;
    }
};
