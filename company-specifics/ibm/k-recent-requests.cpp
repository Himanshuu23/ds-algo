#include <bits/stdc++.h>
using namespace std;

vector<string> getKRecentRequests(int n, int k, vector<string> requests) {
    unordered_map<string, bool> check;
    vector<string> ans;

    for (int i = n-1; i>=0; i--) {
        string request = requests[i];
        if (!k) return ans;
        else if (!check[request]) {
            check[request] = true;
            ans.push_back(request);
        }
    }

    return ans;
}

int main() {
    int n, k; cin >> n >> k;
    cin.ignore();
    vector<string> v(n), ans(k);
    for (int i = 0; i < n; i++) getline(cin, v[i]);

    ans = getKRecentRequests(n, k, v);
    for (auto s : ans) cout << s << " ";
    cout << endl;
}
