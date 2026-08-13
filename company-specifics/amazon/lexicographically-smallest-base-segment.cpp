#include <bits/stdc++.h>
using namespace std;

/*
In a distributed storage system, certain data represented as a string missingData needs to be recovered.To restore the data, you must choose a string baseSegment of length segmentSize. The system repeatedly appends copies of baseSegment to an initially empty string until the frequency of every character in the accumulated string is greater than or equal to its frequency in missingData.TaskFind and return the baseSegment of length segmentSize that satisfies the following conditions:Requires the minimum number of replications (copies) to meet or exceed all character counts in missingData.If multiple valid baseSegment options achieve the minimum number of replications, return the lexicographically smallest one.If no such segment can be formed (e.g., segmentSize is insufficient or contains characters not present in missingData), return "-1".Constraints$1 \le \text{segmentSize} \le 2 \times 10^5$$1 \le \vert{}\text{missingData}\vert{} \le 2 \times 10^5$missingData contains only lowercase English letters ('a' through 'z').ExamplesExample 1Input: segmentSize = 2, missingData = "aavvavv"Output: "av"Explanation:Character counts in missingData: 'a': 3, 'v': 4.Choosing baseSegment = "av" (1 'a', 1 'v') requires $\max(\lceil 3/1 \rceil, \lceil 4/1 \rceil) = 4$ replications.Both "av" and "va" require 4 replications, but "av" is lexicographically smaller.Example 2Input: segmentSize = 4, missingData = "abacbca"Output: "aabc"
Link - https://www.desiqna.in/19282/amazon-sde-intern-questions-amazon-questions-kumar-july-2026
*/

// find total distinct characters in missingData if they're greater than segmentSize -> -1 (not possible)
// find minimum value of k (replications needed) using binary search -> [count[char] / k]
// hence characters required count[char] / k -> rounded up
// if still not segmentSize then append 'a' infront to make it lexicographically smallest -> sort the answer
// O(|S| + 26log|S|) = O(|S|), O(1)
string getSmallestBaseSegment(int segmentSize, string missingData) {
    vector<int> count(26, 0);
    int distincts = 0;
    for (char c : missingData) {
        if (count[c - 'a'] == 0) distincts++;
        count[c - 'a']++;
    }

    if (distincts > segmentSize) return "-1";

    auto canForm = [&](int k) {
        long long needed = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) { 
                needed += (count[i] + k - 1) / k;
            }
        }
        
        return needed <= segmentSize;
    };

    int low = 1, high = missingData.size();
    int min_k = high;
    while (low <= high) {
        int middle = low + (high - low) / 2;
        if (canForm(middle)) {
            min_k = middle;
            high = middle - 1;
        } else {
            low = middle + 1;
        }
    }

    vector<int> frequency(26, 0);
    int used = 0;
    for (int i = 0; i < 26; i++) {
        if (count[i] > 0) {
            frequency[i] = (count[i] + min_k - 1) / min_k;
            used += frequency[i];
        }
    }

    frequency[0] += segmentSize - used;
    
    string result = "";
    for (int i = 0; i < 26; i++) {
        result.append(frequency[i], 'a' + i);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int segmentSize; cin >> segmentSize;
        string missingData; cin >> missingData;
        cout << getSmallestBaseSegment(segmentSize, missingData) << '\n';
    }

    return 0;
}
