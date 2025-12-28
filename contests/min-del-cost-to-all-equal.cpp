#include<bits/stdc++.h>
using namespace std;
using ll = long long;

char maxIndex(const string& s, vector<int>& v) {
    unordered_map<char, ll> map(26);
    char maxChar;
    
    for (int i = 0; i < s.size(); i++) {
        char curr = s[i];
        map[curr] += v[i];
        if (map[curr] > map[maxChar]) maxChar = curr;
    }

    return maxChar;
}

ll minCost(string s, vector<int>& cost) {
    ll answer = 0;

    char maxChar = maxIndex(s, cost);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != maxChar) answer += cost[i];
    }

    return answer;
}

int main() {
    string s; cin >> s;
    cin.ignore();

    int n = s.size();
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    cout << minCost(s, v) << endl;
}
