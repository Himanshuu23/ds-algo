#include <bits/stdc++.h>
using namespace std;

// using recursion - o(3^n), O(n) - for the recursion stack
class Solution {
public:
    int tribonacci(int n) {
        if (n <= 2) {
            return n == 0 ? 0 : 1;
        }

        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
    }
};

// using top down dp - o(n), O(n)
class Solution2 {
private:
    unordered_map<int, int> cache;
public:
    int tribonacci(int n) {
        if (n <= 2) {
            return n == 0 ? 0 : 1;
        }
        if (cache.count(n)) return cache[n];

        return cache[n] = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
    }
};

// bottom up dp: O(n), O(n)
class Solution3 {
public:
    int tribonacci(int n) {
        if (n <= 2) {
            return n == 0 ? 0 : 1;
        }

        vector<int> dp(n + 1, 0);
        dp[1] = dp[2] = 1;

        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
        }

        return dp[n];
    }
};

// space optimized dp: O(n), O(1)
class Solution4 {
public:
    int tribonacci(int n) {
        int t[] = {0, 1, 1};
        if (n < 3) return t[n];

        for (int i = 3; i <= n; i++) {
            t[i % 3] = t[0] + t[1] + t[2];
        }

        return t[n % 3];
    }
};

// using matrix exponentiation - O(logn), O(1)
class Solution5 {
private:
    vector<vector<long long>> matrixMultiplication(vector<vector<long long>>& A, vector<vector<long long>>& B) {
        vector<vector<long long>> matrix(3, vector<long long> (3, 0));
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    matrix[i][j] += A[i][k] * B[k][j]; 
                }
            }
        }

        return matrix;
    }

    vector<vector<long long>> matrixPower(vector<vector<long long>>& M, int p) {
        vector<vector<long long>> result = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        vector<vector<long long>> base = M;

        while (p > 0) {
            if (p % 2 == 1) {
                result = matrixMultiplication(result, base);
            }
            base = matrixMultiplication(base, base);
            p /= 2;
        }

        return result;
    }
public:
    int tribonacci(int n) {
        if (n <= 2) {
            return n == 0 ? 0 : 1;
        }

        vector<vector<long long>> M = {{1, 1, 1}, {1, 0, 0}, {0, 1, 0}};
        vector<vector<long long>> result = matrixPower(M, n - 1); // since M^n finds T(n+1) where T(n) is nth tribonacci number

        return result[0][0];
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
