#include <bits/stdc++.h>
using namespace std;

// twist is: a negative value can make a very large value very small and vice-versa and also a zero breaks the product completely to zero
// trying all possible subarrays and tracking the best product - even single elements one's are needed to be tracked
// O(n^2), O(1)
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int answer = nums[0];
        for (int i = 0; i < n; i++) {
            int current = nums[i];
            answer = max(answer, current);
            for (int j = i + 1; j < n; j++) {
                current *= nums[j];
                answer = max(answer, current);
            }
        }

        return answer;
    }
};

// using kadane's: currentMax = maximum product ending at this index, currentMin = minimum product ending at this index. If the current number is negative, mutliplying it with currentMinimum might product a new maximum. Zeroes are naturally handled since multiplying nums[i] would reset the product. O(n), O(1)
class Solution2 {
public:
    int maxProduct(vector<int>& nums) {
		int answer = nums[0], currentMin = nums[0], currentMax = nums[0]; 
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] < 0) swap(currentMin, currentMax);
			currentMax = max(nums[i], nums[i] * currentMax);
			currentMin = min(nums[i], nums[i] * currentMin);
			answer = max(answer, currentMax);
		}
		return answer;
    }
};

// using prefix, suffix: when there are even number of negatives then complete array. If odd number of negatives then answer would be due to two ways: (i) removing either prefix upto first negative (ii) removing suffix after last negative. Since removing more than one negatives is bad since we would be losing more numbers. So we can do two runs one for suffix and one for prefix and get the max answer from each. So, we don't have to track negatives either. O(n), O(1)
class Solution3 {
public:
    int maxProduct(vector<int>& nums) {
		int n = nums.size(), answer = nums[0];
		int prefix = 0, suffix = 0;
		for (int i = 0; i < n; i++) {
			prefix = nums[i] * (prefix == 0 ? 1 : prefix);
			suffix = nums[n - i - 1] * (suffix == 0 ? 1 : suffix);
			answer = max({answer, prefix, suffix});
		}
		return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
