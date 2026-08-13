#include <bits/stdc++.h>
using namespace std;

/*
A hiring team needs to form a valid non-empty team of candidates based on their potential. You are given an array potential of size n, and two integers l (minimum potential) and m (maximum potential).A candidate is eligible to be in the team if their potential lies in the inclusive range $[l, m]$.TaskCalculate the total number of possible ways to form a non-empty team using only eligible candidates.Input FormatAn integer n: Total number of candidates.An integer l: Minimum required potential score.An integer m: Maximum required potential score.An integer array potential of size n: Potential scores of each candidate.Output FormatReturn a single integer representing the total number of valid non-empty team combinations.ExampleInput:n = 6l = 2, m = 8potential = [4, 5, 7, 1, 9, 10]Output: 7Explanation:Candidates within range $[2, 8]$ are [4, 5, 7] (total $k = 3$ eligible candidates).1-member teams: $\{4\}, \{5\}, \{7\}$ (3 ways)2-member teams: $\{4,5\}, \{5,7\}, \{4,7\}$ (3 ways)3-member team: $\{4,5,7\}$ (1 way)Total ways = $3 + 3 + 1 = 7$.
Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/
*/

const int MOD = 1e9 + 7;
// Binary exponentiation - O(logk)
long long power(long long base, long long exp) {
    long long result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 != 0) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return result;
}

// if there are 'k' eligible candidates then each of those have two choices either form a team or don't form a team -> basically finding subsets which is 2^k but remove the empty subset since teams must be non-empty -> 2^k - 1
// O(n), O(1), if n is very large use binary exponentiation
long long countValidTeams(int n, int l, int m, vector<int>& potential) {
    int eligibleCandidates = 0;
    for (int candidate : potential) {
        if (candidate >= l && candidate <= m) eligibleCandidates++;
    }

    if (eligibleCandidates == 0) return 0;
    long long answer = power(2, eligibleCandidates) - 1;
    // return (1LL << eligibleCandidates) - 1;
    
    // handles negative result if power returned zero i.e. answer = 0 - 1 = -1
    if (answer < 0) answer += MOD;

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, l, m; cin >> n >> l >> m;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }

        cout << countValidTeams(n, l, m, v) << '\n';
    }

    return 0;
}
