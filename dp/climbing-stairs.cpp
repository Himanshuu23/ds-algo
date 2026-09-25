#include <bits/stdc++.h>
using namespace std;

// recursion - O(2^n), O(n)
class Solution {
private:
    int dfs(int n, int i) {
        if (i >= n) return i == n; // if i == n then one valid way, i > n then 0 valid way

        return dfs(n, i + 1) + dfs(n, i + 2); // from step 0 taking one and two steps
    }
public:
    int climbStairs(int n) {
        return dfs(n, 0);
    }
};

// caching previous solution - top down dp: O(n), O(n)
class Solution2 {
private:
    vector<int> cache;
    int dfs(int n, int i) {
        if (i >= n) return i == n; // if i == n then one valid way, i > n then 0 valid way
        if (cache[i] != -1) return cache[i];
        return cache[i] = dfs(n, i + 1) + dfs(n, i + 2); // from step 0 taking one and two steps
    }
public:
    int climbStairs(int n) {
        cache.resize(n + 1, -1);
        return dfs(n, 0);
    }
};

// bottom up dp: O(n), O(n)
class Solution3 {
public:
    int climbStairs(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 0; i <= n; i++) {
            if (i - 1 >= 0) dp[i] += dp[i-1];
            if (i - 2 >= 0) dp[i] += dp[i-2];
        }

        return dp[n];
    }
};

// bottom up dp: O(n), O(1)
class Solution4 {
public:
    int climbStairs(int n) {
        int f[] = {1, 1};

        for (int i = 2; i <= n; i++) {
            f[i % 2] = f[0] + f[1];
        }

        return f[n % 2];
    }
};

// Using Matrix Exponentiation: O(logn), O(1)
// Since the solution follows fibonacci sequence we can use matrix exponentiation to find the answer in logn rather than linear time
// |1 1| -> f(n) = 1*f(n-1) + 1*f(n-2)
// |1 0| -> f(n-1) = 1*f(n-1) + 0*f(n-2)
// squares the matrix 'n' times and [0][0] element is the answer.
// M⁴ = (M²)² — just 2 multiplications instead of 4
// M⁸ = (M⁴)² — just 3 multiplications instead of 8
// M¹⁶ = (M⁸)² — just 4 multiplications instead of 16
// so works just like binary exponentiation
class Solution5 {
private:
    vector<vector<int>> matrixMultiplication(vector<vector<int>>& A, vector<vector<int>>& B) {
        return {{A[0][0] * B[0][0] + A[0][1] * B[1][0],
                 A[0][0] * B[0][1] + A[0][1] * B[1][1]},
                {A[1][0] * B[0][0] + A[1][1] * B[1][0],
                 A[1][0] * B[0][1] + A[1][1] * B[1][1]}};
    }

    // just binary exponentiation but for matrices
    vector<vector<int>> matrixPower(vector<vector<int>>& M, int p) {
        vector<vector<int>> result = {{1, 0}, {0, 1}}; // starting from identity matrix
        vector<vector<int>> base = M;

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
    int climbStairs(int n) {
        if (n == 1) return 1;

        vector<vector<int>> M = {{1, 1}, {1, 0}};
        vector<vector<int>> result = matrixPower(M, n);

        return result[0][0];
    }
};

// using math - using binet's formula: since fibonacci sequence can be represented in the form of two constants derived from golden ration. Compute the golden ratio φ = (1 + √5) / 2 and its conjugate ψ = (1 − √5) / 2. Climbing stairs is going from 0 start to nth stair so fib(n+1)
// O(1), O(1)
class Solution6 {
public:
    int climbStairs(int n) {
        double sqrt5 = sqrt(5);
        double phi = (1 + sqrt5) / 2;
        double psi = (1 - sqrt5) / 2;
        n++;
        return round((pow(phi, n) - pow(psi, n)) / sqrt5); // rounding to the nearest integer
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
