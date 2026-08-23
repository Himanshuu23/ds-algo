#include <bits/stdc++.h>
using namespace std;

// using sorting - O(m*nlogn), O(n), m -> number of calls made
class KthLargest {
private:
    vector<int> v;
    int k;
public:
    KthLargest(int k, vector<int>& nums) {
        v = nums;
        this->k = k;
    }
    
    int add(int val) {
        v.push_back(val);
        sort(v.begin(), v.end());
        return v[v.size() - k];
    }

    // in sorted array: kth largest = nums[n - k], kth smallest = nums[k-1]
};

// using minHeap - O(nlogk), O(k) - minHeap holds k smallest elements now if we keep k largest elements in it then top smallest would be kth largest and since we keep 'k' size heap means we pop (smallest element) when size of heap > k means we're keeping k largest elements in the heap at the end - hence we can get the kth largest in O(1)
class KthLargest2 {
private:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
public:
    KthLargest2(int k, vector<int>& nums) {
        this->k = k;
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }
    }
    
    int add(int val) {
        pq.push(val);
        if (pq.size() > k) {
            pq.pop();
        }
        return pq.top();
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
