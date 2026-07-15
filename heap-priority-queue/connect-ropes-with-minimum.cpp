/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        priority_queue<int, vector<int>, greater<>> pq;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            pq.push(x);
        }

        int answer = 0;
        while (pq.size() != 1) {
            int first = pq.top(); pq.pop();
            int second = pq.top(); pq.pop();
            answer += first + second;
            pq.push(first + second);
        }
        cout << answer << '\n';
    }

    return 0;
}
