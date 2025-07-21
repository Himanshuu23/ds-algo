/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Coder {
public:
	string encode(vector<string>& w) {
		string s = "";
		for (string c : w) s += to_string(c.size()) + "#" + c;
		return s;
	}

    vector<string> decode(string s) {
        vector<string> ans;
        int i(0);
        while (i < s.size()) {
            int j = i;
            while (s[j] != '#') j++;
            int len = stoi(s.substr(i, j - i));
            ans.push_back(s.substr(j+1, len));
            i = j + 1 + len;
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
	    int n; cin >> n;
	    vector<string> v(n);

	    for (int i = 0; i < n; i++) cin >> v[i];
        Coder c;
        string ans = c.encode(v); cout << ans << endl;
        vector<string> a = c.decode(ans);
        for (string s : a) cout << s << " ";
        cout << endl;
    }

    return 0;
}
