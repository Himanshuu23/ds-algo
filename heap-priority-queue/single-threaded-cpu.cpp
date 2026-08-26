#include<bits/stdc++.h>
using namespace std;

/*
brute force: keep a timer, available array, processed set
run a loop and find the ones with time less than or equal to timer and put them them in available then traverse available and choose the one with least processing time and least index if processing time clashes - run those and again repeat this technique
increase the timer by processing time as well and put that task in processed
also make sure to include idle time - that is when 
O(n^2) - since we repeat this work unless size of processed is n
*/
class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<bool> processed(n, false);
        vector<int> answer;

        long long timer = 0;

        for (int count = 0; count < n; count++) {
            int best = -1;

            // find available task with smallest processing time, and smallest index on tie
            for (int i = 0; i < n; i++) {
                if (!processed[i] && tasks[i][0] <= timer) {
                    if (best == -1 || tasks[i][1] < tasks[best][1] || (tasks[i][1] == tasks[best][1] && i < best)) {
                        best = i;
                    }
                }
            }

            // CPU is idle -> jump to next task's enqueue time
            if (best == -1) {
                for (int i = 0; i < n; i++) {
                    if (!processed[i] && (best == -1 || tasks[i][0] < tasks[best][0])) {
                        best = i;
                    }
                }

                timer = tasks[best][0];

                // find the best again now that tasks are available
                for (int i = 0; i < n; i++) {
                    if (!processed[i] && tasks[i][0] <= timer) {
                        if (best == -1 ||
                            tasks[i][1] < tasks[best][1] ||
                            (tasks[i][1] == tasks[best][1] && i < best)) {
                            best = i;
                        }
                    }
                }
            }
            
            // process task
            answer.push_back(best);
            processed[best] = true;
            timer += tasks[best][1]; 
        }

        return answer;
    }
};

/*
Optimization: we always want the best possible available task - now instead of traversing the elements again we can maintain a heap of all available since of all them would be having clashing enqueue time - we need the one with min processing time and if that also clashes then based on smallest index - heap can do this in logn time so overall complexity becomes nlogn
we first sort based on enqueue_time and heap would have based on processing_time and index since we only wanna compare the available ones. We cannot push [enqueue_time, processing_time, index] because suppose [4,5] and [5,1] both are available the heap would give [4,5] since enqueue time is smaller but CPU wants the one which has less processing time
and also this way heap only stores the current available values and not all together so memory efficient
O(nlogn), O(n)
*/
class Solution2 {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        int n = tasks.size();
        vector<int> answer;
        
        vector<tuple<int, int, int>> sorted;
        for (int i = 0; i < n; i++) {
            sorted.push_back({ tasks[i][0], tasks[i][1], i});
        }
        sort(sorted.begin(), sorted.end());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        long long timer = 0;
        int i = 0;

        while (i < n || !minHeap.empty()) {
            // if nothing is availabe, jump to next enqueue time
            if (minHeap.empty()) {
                timer = max(timer, (long long)get<0>(sorted[i]));
            }

            // add all currently available tasks
            while (i < n && get<0>(sorted[i]) <= timer) {
                minHeap.push({get<1>(sorted[i]), get<2>(sorted[i])});
                i++;
            }

            // pick shortest processing time, then smallest index if tie
            auto [processing_time, index] = minHeap.top();
            minHeap.pop();
            answer.push_back(index);
            timer += processing_time;
        }

        return answer;
    }
};
