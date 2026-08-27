#include <bits/stdc++.h>
using namespace std;

// brute force: O(n*k) from all possible projects available for current capital we have choose the one with most profit - greedy
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = capital.size(), answer = w;
        vector<int> visited(n, 0);
        while (k--) {
            int best = -1;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && answer >= capital[i]) {
                    if (best == -1) {
                        best = i;
                        visited[i] = 1;
                    } else if (profits[best] < profits[i]) {
                        visited[best] = 0;
                        best = i;
                        visited[i] = 1;
                    }
                }
            }
            
            if (best == -1) {
                break;
            }

            answer += profits[best];
        }
        
        return answer;
    }
};

// O(nlogn) - using maxHeap - sort by capital - inside maxHeap push all affordable profits - k times pop
class Solution2 {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int n = profits.size();
        vector<int> indices(n);
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return capital[a] < capital[b];
        });

        priority_queue<int> maxProfit;
        int index = 0;
        for (int i = 0; i < k; i++) {
            while (index < n && capital[indices[index]] <= w) {
                maxProfit.push(profits[indices[index]]);
                index++;
            }
            if (maxProfit.empty()) {
                break;
            }
            w += maxProfit.top();
            maxProfit.pop();
        }

        return w;
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
