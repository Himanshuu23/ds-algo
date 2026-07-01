#include <bits/stdc++.h>
using namespace std;

void usingDeque() {
    int n; cin >> n;
    vector<int> v(2*n);
    for (int i = 0; i < n; i++) cin >> v[i];
    for (int i = n; i < 2*n; i++) v[i] = v[i-n];

    vector<long long> prefix(2*n);
    prefix[0] = v[0];
    for (int i = 1; i < 2*n; i++) prefix[i] = v[i] + prefix[i-1];

    long long answer = INT_MIN;
    deque<int> dq;
    for (int i = 0; i < 2*n; i++) {
        while (!dq.empty() && dq.front() < i - n) dq.pop_front();
        if (!dq.empty())
            answer = max(answer, prefix[i] - prefix[dq.front()]);
        while (!dq.empty() && prefix[dq.back()] >= prefix[i]) dq.pop_back();
        dq.push_back(i);
    }

    cout << answer << '\n';
}

int kadane(vector<int>& arr, int n) {
    int currSum = 0, maxSum = INT_MIN;
    for (int i = 0; i < n; i++) {
        currSum = max(arr[i], currSum + arr[i]);
        maxSum = max(maxSum, currSum);
    }
    return maxSum;
}

int main() {
    int n; cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) cin >> arr[i];

    int totalSum = 0, wrapSum, nonWrapSum = kadane(arr, n);
    
    if (nonWrapSum < 0) { // when all the elements are negative
        return nonWrapSum;
    }

    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
        arr[i] = -arr[i];
    }

    wrapSum = totalSum + kadane(arr, n);
    cout << max(wrapSum, nonWrapSum) << endl;
    
    return 0;
}
