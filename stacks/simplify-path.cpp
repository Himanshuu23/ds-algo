#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> st;
        string current;
        for (char c : path + "/") {
            if (c == '/') {
                if (current == "..") {
                    if (!st.empty()) st.pop_back();
                } else if (!current.empty() && current != ".") {
                    st.push_back(current);
                }
                current.clear();
            } else {
                current += c;
            }
        }

        string answer = "/";
        for (int i = 0; i < st.size(); i++) {
            if (i == st.size() - 1) answer += st[i];
            else answer += st[i] + "/";
        }
        
        return answer;
    }
};
