#include <bits/stdc++.h>
using namespace std;

// its graph connectivity problem - if two accounts share an email, they belong to the same person and should be merged. We can model this into a graph where each nodes is email and all emails belonging to the same account are connected to each other now we just have to group each connected component together.
// Using DFS - O((n * m)log(n * m)), O(n * m)
class Solution {
private:
    unordered_map<string, int> emailIndex; // email -> id        
    vector<string> emails; // set of emails of all accounts
    unordered_map<int, int> emailToAccount; // mapping email id -> account id 
    vector<vector<int>> adj;
    unordered_map<int, vector<string>> emailGroup; // mapping account id -> all of its emails
    vector<bool> visited;

    void dfs(int node, int accountId) {
        visited[node] = true;
        emailGroup[accountId].push_back(emails[node]);
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, accountId);
            }
        }
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        int m = 0;

        // build email index and mappings
        for (int accountId = 0; accountId < n; accountId++) {
            vector<string>& account = accounts[accountId];
            for (int i = 1; i < account.size(); i++) {
                string email = account[i];
                if (emailIndex.find(email) == emailIndex.end()) {
                    emails.push_back(email);
                    emailIndex[email] = m;
                    emailToAccount[m] = accountId;
                    m++;
                }
            }
        }

        // building graph
        adj.resize(m);
        for (auto& account : accounts) {
            for (int i = 2; i < account.size(); i++) {
                int id1 = emailIndex[account[i]];
                int id2 = emailIndex[account[i-1]];
                adj[id1].push_back(id2);
                adj[id2].push_back(id1);
            }
        }

        visited.resize(m, false);
        for (int i = 0; i < m; i++) {
            if (!visited[i]) {
                int accountId = emailToAccount[i];
                dfs(i, accountId);
            }
        }

        // building result
        vector<vector<string>> result;
        for (auto& [accountId, group] : emailGroup) {
           sort(group.begin(), group.end());
           vector<string> merged;
           merged.push_back(accounts[accountId][0]);
           merged.insert(merged.end(), group.begin(), group.end());
           result.push_back(merged);
        }

        return result;
    }
};

// just bfs in place of dfs - everything same
class Solution2 {
private:
    unordered_map<string, int> emailIndex; // email -> id        
    vector<string> emails; // set of emails of all accounts
    unordered_map<int, int> emailToAccount; // mapping email id -> account id 
    vector<vector<int>> adj;
    unordered_map<int, vector<string>> emailGroup; // mapping account id -> all of its emails
    vector<bool> visited;

    void bfs(int node, int accountId) {
        queue<int> q;
        q.push(node);
        visited[node] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            emailGroup[accountId].push_back(emails[current]);
            for (int neighbor : adj[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        int m = 0;

        // build email index and mappings
        for (int accountId = 0; accountId < n; accountId++) {
            vector<string>& account = accounts[accountId];
            for (int i = 1; i < account.size(); i++) {
                string email = account[i];
                if (emailIndex.find(email) == emailIndex.end()) {
                    emails.push_back(email);
                    emailIndex[email] = m;
                    emailToAccount[m] = accountId;
                    m++;
                }
            }
        }

        // building graph
        adj.resize(m);
        for (auto& account : accounts) {
            for (int i = 2; i < account.size(); i++) {
                int id1 = emailIndex[account[i]];
                int id2 = emailIndex[account[i-1]];
                adj[id1].push_back(id2);
                adj[id2].push_back(id1);
            }
        }

        visited.resize(m, false);
        for (int i = 0; i < m; i++) {
            if (!visited[i]) {
                int accountId = emailToAccount[i];
                bfs(i, accountId);
            }
        }

        // building result
        vector<vector<string>> result;
        for (auto& [accountId, group] : emailGroup) {
           sort(group.begin(), group.end());
           vector<string> merged;
           merged.push_back(accounts[accountId][0]);
           merged.insert(merged.end(), group.begin(), group.end());
           result.push_back(merged);
        }

        return result;
    }
};

// using dsu - just all emails which have the same emails connect them to the same parent (accountId)
// same complexity
class DSU {
    public:
        vector<int> parent, _rank;
        
        DSU (int n) {
            _rank.assign(n, false);
            parent.resize(n);
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unite(int x, int y) {
            int rootX = find(x), rootY = find(y);

            if (rootX == rootY) return;

            if (_rank[rootX] < _rank[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            if (_rank[rootX] == _rank[rootY]) _rank[rootX]++;
        }
};
class Solution3 {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DSU dsu(n);

        unordered_map<string, int> emailToAccount; // email id to account Id
        
        // building dsu structure
        for (int accountId = 0; accountId < n; accountId++) {
            for (int emails = 1; emails < accounts[accountId].size(); emails++) {
                string email = accounts[accountId][emails];
                if (emailToAccount.count(email)) { // if email was seen before unite current owner with that previous owner
                    dsu.unite(accountId, emailToAccount[email]);
                } else { // else record current owner
                    emailToAccount[email] = accountId;
                }
            }
        } 

        // group emails by parent account
        map<int, vector<string>> emailGroup;
        for (auto [email, accountId] : emailToAccount) { // find parent account owner of each email and grouping them by parent: [emails...]
            int parent = dsu.find(accountId);
            emailGroup[parent].push_back(email);
        }

        // building result
        vector<vector<string>> result;
        for (auto& [accountId, emails] : emailGroup) {
            sort(emails.begin(), emails.end());
            vector<string> merged;
            merged.push_back(accounts[accountId][0]);
            merged.insert(merged.end(), emails.begin(), emails.end());
            result.push_back(merged);
        }

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
