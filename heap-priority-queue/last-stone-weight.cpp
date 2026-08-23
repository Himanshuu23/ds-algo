#include <bits/stdc++.h>
using namespace std;

// using sorting - n^2log(n)
class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        while (stones.size() > 1) {
            int n = stones.size();
            sort(stones.begin(), stones.end());
            int current = stones[n-1] - stones[n-2];
            stones.pop_back();
            stones.pop_back();
            if (current != 0) {
                stones.push_back(current);
            }
        }

        return stones.empty() ? 0 : stones[0];
    }
};

// using binary search - to avoid sorting again and again - we can place the new current to be insert at the correct position to keep the array sorted - O(n^2)
class Solution2 {
public:
    int lastStoneWeight(vector<int>& stones) {
        sort(stones.begin(), stones.end());
        int n = stones.size();

        while (n > 1) {
            int current = stones[n-1] - stones[n-2];
            n -= 2;
            if (current > 0) {
                int l = 0, r = n;
                while (l < r) {
                    int middle = (l + r) / 2;
                    if (stones[middle] < current) {
                        l = middle + 1;
                    } else {
                        r = middle;
                    }
                }
                int position = l;
                stones.push_back(0);
                for (int i = n + 1; i > position; i--) {
                    stones[i] = stones[i-1];
                }
                stones[position] = current;
                n++;
            }
        }
        return n > 0 ? stones[0] : 0;
    }
};

// max heap - O(nlogn), O(n)
class Solution3 {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
        for (int s : stones) {
            pq.push(s);
        }

        while (pq.size() > 1) {
            int first = pq.top();
            pq.pop();
            int second = pq.top();
            pq.pop();
            int current = first - second;
            if (current > 0) {
                pq.push(current);
            }
        }

        pq.push(0);
        return pq.top();
    }
};

// bucket sort - O(n+w), O(w), w - weight of the heaviest stone
class Solution4 {
public:
    int lastStoneWeight(vector<int>& stones) {
        int maxStone = 0;

        // finding the max weight
        for (int stone : stones) {
            maxStone = max(maxStone, stone);
        }

        vector<int> bucket(maxStone + 1, 0);

        // frequency of each stone's weight
        for (int stone : stones) {
            bucket[stone]++;
        }

        int first = maxStone, second = maxStone;
        // while there's stone of weight = first
        while (first > 0) {
            // if count is even then all would cancel each other out - try smaller weight
            if (bucket[first] % 2 == 0) {
                first--;
                continue;
            }

            // if weight is odd then one remains
            // now j = weight of next heaviest stone
            int j = min(first - 1, second);
            while (j > 0 && bucket[j] == 0) {
                j--;
            }

            // if there is no next heaviest stone then this remaining first is the remaining stone
            if (j == 0) {
                return first;
            }

            // otherwise smashing them
            second = j;
            bucket[first]--;
            bucket[second]--;
            bucket[first - second]++;

            // moving first to next relevant weight
            first = max(first - second, second);
        }

        return first;
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
