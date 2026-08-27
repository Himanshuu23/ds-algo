/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// brute force: addNum() - O(m * nlogn), findMedian() - O(1), space - O(n) -> m is number of function calls
class MedianFinder {
    vector<int> v;
public:
    MedianFinder() {}
    
    void addNum(int num) {
        v.push_back(num);
        sort(v.begin(), v.end());
    }
    
    double findMedian() {
        int n = v.size();
        if (n & 1) {
            return (double)v[n/2];
        } else {
            return (v[(n-1)/2] + v[n/2]) / 2.0;
        }
    }
};

// maintaining minHeap -> stores right half of sorted array with smallest element on the top, maxheap - stores the left half of the sorted array and top is the largest in that. Now if n is odd then median is top of maxHeap else avarage of top of both hence O(logn), O(n)
// Difference of total elements in each must be atmost 1
class Stream{
    priority_queue<int> mxh;
    priority_queue<int, vector<int>, greater<int>> mnh;

public:
    // if maxHeap is not empty and incoming value is smaller than smallest element in maxHeap then insert into maxHeap. Otherwise insert into minHeap. Now rebalancing, if one heap becomes larger than the other by more than one, move the top element to other heap
    void addNum(int value) {
        if (mxh.empty() || value <= mxh.top()) mxh.push(value);
        else mnh.push(value);

        if (mxh.size() > mnh.size() + 1) {
            mnh.push(mxh.top());
            mxh.pop();
        } else if (mnh.size() > mxh.size() + 1) {
            mxh.push(mnh.top());
            mnh.pop();
        }
    }

    // if both heap have same number of elements - average of their tops, else top of heap with more elements
    double getMedian() {
        int mx = mxh.size(), mn = mnh.size();
        return ((mx + mn) % 2 == 0) ? (mxh.top() + mnh.top()) / 2.0 : (mx > mn ) ? mnh.top() : mxh.top();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        Stream s;
        s.addNum(5);
        s.addNum(2);
        s.addNum(10);
        s.addNum(1);
        cout << s.getMedian() << endl;
    }

    return 0;
}
