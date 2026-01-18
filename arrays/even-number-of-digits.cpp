class Solution {
public:
    bool hasEvenDigits(int n) {
        int count(0);
        while (n) {
            count++;
            n /= 10;
        }

        return (count % 2 == 0) ? true : false; 
    }

    int findNumbers(vector<int>& nums) {
        int answer(0);
        for (auto& num : nums) if (hasEvenDigits(num)) answer++;
        return answer; 
    }
};
