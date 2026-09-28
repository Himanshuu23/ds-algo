#include <bits/stdc++.h>
using namespace std;

// O(max(n, m)), O(n + m) - two pointers
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    vector<int> result;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] <= b[j]) {
            result.push_back(a[i++]);
        } else {
            result.push_back(b[j++]);
        }
    }
    while (i < n) result.push_back(a[i++]);
    while (j < m) result.push_back(b[j++]);
    for (int x : result) cout << x << " ";
    cout << '\n';
    return 0;
}

// O(max(n, m)), O(1) - two pointers
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int last = n + m - 1;
		while (m > 0 && n > 0) {
			if (nums1[m-1] > nums2[n-1]) {
				nums1[last] = nums1[m-1];
				m--;
			} else {
				nums1[last] = nums2[n-1];
				n--;
			}
			last--;
		}

		while (n > 0) {
			nums1[last] = nums2[n-1];
			n--; last--;
		}
    }
};
