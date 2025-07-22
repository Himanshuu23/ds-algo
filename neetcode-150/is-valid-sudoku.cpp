/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct pair_hash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

bool solve(vector<vector<char>>& v) {
    unordered_map<int, unordered_set<char>> row, col;
    unordered_map<pair<int, int>, unordered_set<char>, pair_hash> square;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c = v[i][j];
            if (c == '.') continue;
            if (row[i].count(c) || col[j].count(c) || square[{i/3, j/3}].count(c)) return false;
            row[i].insert(c); col[j].insert(c); square[{i/3, j/3}].insert(c);
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
	    vector<vector<char>> v(9, vector<char>(9));
	    for (int i = 0; i < 9; i++)
		    for (int j = 0; j < 9; j++)
			    cin >> v[i][j];
        puts(solve(v) ? "Yes\n" : "No\n");
    }

    return 0;
}
