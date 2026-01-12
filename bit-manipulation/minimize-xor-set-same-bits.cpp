class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int current = __builtin_popcount(num1);
        int target = __builtin_popcount(num2);
        int answer = num1;

        for (int i = 0; i < 32; i++) {
            if (current > target && (1 << i) & num1) {
                answer ^= 1 << i;
                --current;
            }
            if (current < target && !((1 << i) & num1)) {
                answer ^= 1 << i;
                ++current;

            }
        }

        return answer;
    }
};
