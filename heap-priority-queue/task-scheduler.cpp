#include<bits/stdc++.h>
using namespace std;

// brute force - making it act as CPU - O(t*n), O(t) where t -> time to process given tasks and n is given cooldown time
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        // count of each task
        for (char task : tasks) {
            count[task - 'A']++;
        }

        // each task - { count, taskID }
        vector<pair<int, int>> arr;
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                arr.emplace_back(count[i], i);
            }
        }

        int time = 0;
        vector<int> processed;
        while (!arr.empty()) {
            int maxIndex = -1;
            for (int i = 0; i < arr.size(); i++) {
                bool flag = true;
                // checking if within last 'n' cycles this task got executed
                for (int j = max(0, time - n); j < time; j++) {
                    // if it did - move to next task
                    if (j < processed.size() && processed[j] == arr[i].second) {
                        flag = false;
                        break;
                    }
                }
                if (!flag) continue;
                // if not then find the task with max number of tasks left
                if (maxIndex == -1 || arr[maxIndex].first < arr[i].first) {
                    maxIndex = i;
                }
            }

            time++;
            int current = -1;
            if (maxIndex != -1) {
                current = arr[maxIndex].second;
                arr[maxIndex].first--; // decreasing task
                if (arr[maxIndex].first == 0) {
                    arr.erase(arr.begin() + maxIndex);
                }
            }
            processed.push_back(current);
        }

        return time;
    }
};

// using maxHeap - gives currently available tasks + the one with highest remaining tasks, queue - tasks inside the cooldown period
// We don't have to check every second - we insert with its next availability time
// O(m), O(1) where m is number of tasks
class Solution2 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        for (char task : tasks) {
            count[task - 'A']++;
        }

        priority_queue<int> maxHeap;
        for (int cnt : count) {
            if (cnt > 0) {
                maxHeap.push(cnt);
            }
        }

        int time = 0;
        queue<pair<int, int>> q; // keeps tasks that are currently in cooldown
        // using queue - since we want first in first out - the task that was pushed earlier will have atleast time 
        while (!maxHeap.empty() || !q.empty()) {
            time++;

            if (maxHeap.empty()) { // nothing available
                time = q.front().second; // skipping the time to next available task directly
            } else {
                // getting the max task and executing it
                int cnt = maxHeap.top() - 1;
                maxHeap.pop();
                if (cnt > 0) {
                    q.push({cnt, time + n});
                }
            }

            // pushing the available elements
            if (!q.empty() && q.front().second == time) {
                maxHeap.push(q.front().first);
                q.pop();
            }
        }

        return time;
    }
};

// greedy - O(m), O(1)
// Let maxFrequency be the task with maximum remaining task. Now we can take each task type as filling slots. Now each task must be atleast 'n' size apart with this maxFrequency count. So gaps would be maxFrequency - 1 and size of each gap would be minimum 'n'. Hence we fill using other tasks and the remaining ones are filled using idle.
// So initially idle_needed = (maxFrequency - 1) * n. Then suppose count of some other task is c then that task can fill min(c, maxFrequency - 1) empty spots - rest are filled using idle
class Solution3 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        for (char task : tasks) {
            count[task - 'A']++;
        }

        sort(count.begin(), count.end());
        int maxFrequency = count[25];
        int idle = (maxFrequency - 1) * n;

        for (int i = 24; i >= 0; i--) {
            idle -= min(maxFrequency - 1, count[i]);
        }

        return max(0, idle) + tasks.size();
    }
};

// using maths - O(m), O(1)
// As task with max frequency decides the structure of the order in which the tasks must be executed - if max task frequency is maxFrequency then gap would be n units apart so again maxFrequency - 1 blocks of min size 'n'. Now one block - task itself + gaps = (n + 1) to reach the next possible task with maxFrequency tasks.
// so time to process all these tasks - (since each requires 1 unit) = (maxFrequency - 1) * (n + 1)
// But also many tasks may have this maxFrequency tasks count so each would copy this structure
// Hence time = (maxFrequency - 1) * (n + 1) + maxCount where maxCount = total tasks with maxFrequency tasks
class Solution4 {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> count(26, 0);
        for (char task : tasks) {
            count[task - 'A']++;
        }

        int maxFrequency = *max_element(count.begin(), count.end());
        int maxCount = 0; // multiple elements might have this maxFrequency
        for (int i : count) {
            if (i == maxFrequency) {
                maxCount++;
            }
        }

        int time = (maxFrequency - 1) * (n + 1) + maxCount;
        return max((int)tasks.size(), time);
    }
};
