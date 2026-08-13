#include <bits/stdc++.h>
using namespace std;

/*
Given an array of integers arr and an integer x, find the total number of pairs of indices $(i, j)$ such that:$i < j$$(arr[i] + arr[j])$ is divisible by xInput Formatarr: An array/vector of $N$ integers.x: An integer divisor ($x > 0$).Output FormatReturn an integer representing the total count of valid pairs.ExampleInput:arr = [3, 8, 2, 7, 1, 9]x = 5Output:4Explanation:The 4 valid pairs $(arr[i], arr[j])$ with $i < j$ whose sum is divisible by 5 are:$(3, 7) \rightarrow 3 + 7 = 10$$(8, 2) \rightarrow 8 + 2 = 10$$(8, 7) \rightarrow 8 + 7 = 15$$(1, 9) \rightarrow 1 + 9 = 10$
Link - https://leetcode.com/discuss/post/5931693/amazon-sde-6m-internship-interview-exper-qy1a/
*/

// brute force - O(N^2), O(1)
int solve(int n, vector<int>& v, int x) {
    int answer = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if ((v[i] + v[j]) % x == 0) ++answer;
        }
    }
    return answer;
}

// O(N), O(X)
// two numbers sum -> multiple of X if their remainders mod to 0 or X
// x is very large then use unordered_map, else to avoid collision vector is fine
long long solve2(int n, vector<int>& v, int x) {
    long long answer = 0;
    vector<int> remainder_map(x, 0);
    for (int val : v) {
        int remainder = (val % x + x) % x; // handles negative numbers as well
        int complement = (x - remainder) % x;
        answer += remainder_map[complement];
        remainder_map[remainder]++;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, x; cin >> n >> x;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        cout << solve2(n, v, x) << '\n';
    }

    return 0;
}
