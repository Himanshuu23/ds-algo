#include <bits/stdc++.h>
using namespace std;

map<string, string> parseJSON(const string &s) {
    map<string, string> mp;
    
    string t = s.substr(1, s.size() - 2);

    stringstream ss(t);
    string part;

    while (getline(ss, part, ',')) {
        int pos = part.find(':');
        string key = part.substr(0, pos);
        string val = part.substr(pos+1);

        key.erase(remove(key.begin(), key.end(), '\"'), key.end());
        val.erase(remove(val.begin(), val.end(), '\"'), val.end());

        mp[key] = val;
    }

    return mp;
}

vector<string> getJSONDiff(string json1, string json2) {
    map<string, string> m1 = parseJSON(json1);
    map<string, string> m2 = parseJSON(json2);

    vector<string> difference;
    
    for (auto &p : m1) {
        string key = p.first;
        if (m2.count(key) && m1[key] != m2[key]) {
            difference.push_back(key);
        }
    }

    sort(difference.begin(), difference.end());
    return difference;
}

int main() {
    string json1, json2;
    cin.ignore();
    getline(cin, json1);
    getline(cin, json2);

    vector<string> result;

    result = getJSONDiff(json1, json2);
    for (auto &s : result) cout << s << " ";
    cout << endl;

    return 0;
}
