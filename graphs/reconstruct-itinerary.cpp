#include <bits/stdc++.h>
using namespace std;

// using dfs: just sorting the neighbors in the adjacency list first and then traversing so we find the lexicographically smaller first. If path through a neighbor works then that is valid solution else backtrack completely for that path and try from other neighbor. Also targetLength = number of edges + 1 since this is like a tree - no cycles (else we would be travelling forever) + we can travel all nodes starting from one but this is not exactly a tree since its not necessary that we can travel from each node to all other node. - basically we have to travel all nodes and there are no cycles.
// O(V * E), O(V * E)
class Solution {
private:
    unordered_map<string, vector<string>> adj;
    vector<string> result;

    bool dfs(const string& source, int targetLength) {
        if (result.size() == targetLength) return true;
        if (adj.find(source) == adj.end()) return false;

        vector<string> temp = adj[source];
        for (int i = 0; i < temp.size(); i++) {
            string v = temp[i];
            adj[source].erase(adj[source].begin() + i);
            result.push_back(v);
            if (dfs(v, targetLength)) return true;
            // backtrack through some other neighbor
            adj[source].insert(adj[source].begin() + i, v);
            result.pop_back();
        }

        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        sort(tickets.begin(), tickets.end());
        
        for (auto& ticket : tickets) {
            adj[ticket[0]].push_back(ticket[1]);
        }

        result.push_back("JFK");
        dfs("JFK", tickets.size() + 1);

        return result;
    }
};

// hierholzer's algorithm : this problem is eulerian path problem: we must visit every node once. this algorithm builds path starting from "JFK" by always taking an available edge, going as deep as possible and adding to the path only when there is no more outgoing edge from the current node. To get lexicographically smallest we have to sort but in the reverse order so we can process the smallest node at the end first and push that to the path. Also since this is recursive the first call would be for the smallest so that would be pushed at the end means we would have to reverse the result at the end.
// O(ElogE), O(E)
class Solution2 {
private:
    unordered_map<string, vector<string>> adj;
    vector<string> result;

    void dfs(const string& source) {
        while (!adj[source].empty()) {
            string destination = adj[source].back();
            adj[source].pop_back();
            dfs(destination);
        }
        result.push_back(source);
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        sort(tickets.rbegin(), tickets.rend());
        for (auto& ticket : tickets) {
            adj[ticket[0]].push_back(ticket[1]);
        }

        dfs("JFK");
        reverse(result.begin(), result.end());
        return result;
    }
};

// iterative method for heirholzer's algorithm - same as above approach just recursion stack -> stack
class Solution3 {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> adj;
        sort(tickets.rbegin(), tickets.rend());
        for (auto& ticket : tickets) {
            adj[ticket[0]].push_back(ticket[1]);
        }

        vector<string> result;
        stack<string> st;
        st.push("JFK");

        while (!st.empty()) {
            string current = st.top();
            if (adj[current].empty()) {
                result.push_back(current);
                st.pop();
            } else {
                string next = adj[current].back();
                adj[current].pop_back();
                st.push(next);
            }
        }

        reverse(result.begin(), result.end());
        return result;
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
