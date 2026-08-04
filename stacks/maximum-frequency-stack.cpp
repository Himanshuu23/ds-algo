#include<bits/stdc++.h>
using namespace std;

// push O(1), pop O(n)
class FreqStack { 
    unordered_map<int, int> mp;
    stack<int> st1, st2;
public:
    FreqStack() {
        
    }
    
    void push(int val) {
        st1.push(val);
        mp[val]++;
    }
    
    int pop() {
        int answer = st1.top();
        while (!st1.empty()) {
            st2.push(st1.top());
            if (mp[answer] < mp[st1.top()]) answer = st1.top();
            st1.pop();
        }
        while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }
        while (!st1.empty() && st1.top() != answer) {
            st2.push(st1.top());
            st1.pop();
        }
        if (!st1.empty()) st1.pop();
        while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
        }

        mp[answer]--;
        return answer;
    }
};

// push, pop O(n)
class FreqStack2 {
    priority_queue<tuple<int, int, int>> pq;
    unordered_map<int, int> mp;
    int index;
public:
    FreqStack2() : index(0) {
        
    }
    
    void push(int val) {
        mp[val]++;
        pq.push({mp[val], index++, val});
    }
    
    int pop() {
        auto top = pq.top();
        pq.pop();
        int value = get<2>(top);
        mp[value]--;
        return value;
    }
};

// O(1) push and pop, O(n) memory
class FreqStack3 {
    unordered_map<int, int> mp;
    unordered_map<int, stack<int>> stacks;
    int maxCount;
public:
    FreqStack3() : maxCount(0) {
        
    }
    
    void push(int val) {
        int valueCount = ++mp[val];
        if (valueCount > maxCount) {
            maxCount = valueCount;
            stacks[valueCount] = stack<int>();
        }
        stacks[valueCount].push(val);
    }
    
    int pop() {
        int answer = stacks[maxCount].top();
        stacks[maxCount].pop();
        mp[answer]--;
        if (stacks[maxCount].empty()) {
            stacks.erase(maxCount);
            maxCount--;
        }
        return answer;
    }
};
