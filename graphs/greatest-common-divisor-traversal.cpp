#include <bits/stdc++.h>
using namespace std;

// using dfs
// brute force solution - for each pairs i and j make a graph - if gcd(i, j) is > 1 then adj[i] will have j and vice versa then in end just dfs to check if all nodes are visited. We only need to do single dfs - "connectivity problem" since this is undirected graph i.e. if gcd(i, j) > 1 means we can travel interval i...j and so all paths are symmetric and transitive that is: symmetric coz if i and can reach j then j can also reach i, transitive: if 0 can reach i and i can reach j means 0 can reach j through i
// O(n^2 * log(max(nums))) though which would tle
class Solution {
private:
    vector<vector<int>> adj;
    vector<bool> visited;

    void dfs(int node) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    }
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        adj.resize(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (gcd(nums[i], nums[j]) > 1) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        visited.assign(n, false);
        dfs(0);

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                return false;
            }
        }

        return true;
    }
};

// using DSU
// To connect the component we don't have to do pairwise comparisons O(n^2) - we connect indices through their prime factors - numbers sharing the prime factors should be in the same component. We maintain a map which represents map[prime_factor] = first index containing that factor. To find the prime factors we use trial division in O(sqrt(n))
// O(m + n(sqrt(m))), O(nlogm): n is size of the array and m is max value in the array - O(m) would be for the dsu and logm would be max height of the tree
class DSU {
    private:
        vector<int> parent, _rank;
        int components;

    public:
        DSU(int n) : parent(n), _rank(n, 1), components(n) {
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
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
            --components;
        }

        bool isConnected() {
            return components == 1;
        }
};

class Solution2 {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        DSU dsu(n);

        unordered_map<int, int> factors;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            int f = 2;
            while (f * f <= num) {
                if (num % f == 0) {
                    if (factors.count(f)) {
                    dsu.unite(i, factors[f]);
                    } else {
                        factors[f] = i;
                    }
                    while (num % f == 0) {
                        num /= f;
                    }
                }
                f++;
            }
            if (num > 1) { // prime number remaining
                if (factors.count(num)) {
                    dsu.unite(i, factors[num]);
                } else {
                    factors[num] = i;
                }
            }
        }

        return dsu.isConnected();
    }
};

// using DSU + sieve of eratosthenes
// we can speed up factorization by precomputing smallest prime factor (spf) for each number using sieve of eratosthenes. with spf we can factorize any number in log(m) time. then we use dsu to connect index directly to virtual nodes representing primes.
// if the array size is greater than 1 and array contains 1 then answer is false since 1 doesn't have any prime factors other than 1 itself, gcd(1, anything) = 1. And so other than caes [1] all cases containing 1 would return false. Since it doesn't shares any factors with anyone.
// DSU would be of size (n + max_element + 1) because now we are not doing union with index with same prime factor but we union i with its prime factors and j with its prime factors and hence if they both have same factors then they end up in the same component
// sieve[x] = spf of x
// In the end just verify that all indices have same parent
// O(m + nlogm), O(n + m) - n is the size of the array and m is the max element of the array
class DSU2 {
    private:
        vector<int> parent, _rank;

    public:
        DSU2(int n) : parent(n), _rank(n, 1) {
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
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
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return true;
        }

        for (int num : nums) {
            if (num == 1) {
                return false;
            }
        }

        int mx = *max_element(nums.begin(), nums.end());
        vector<int> sieve(mx + 1, 0);
        for (int p = 2; p * p <= mx; p++) {
            if (sieve[p] == 0) {
                for (int composite = p * p; composite <= mx; composite += p) {
                    sieve[composite] = p;
                }
            }
        }

        DSU2 dsu(n + mx + 1);
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (sieve[num] == 0) { // prime number
                dsu.unite(i, n + num); // it is its own factor
                continue;
            }

            while (num > 1) {
                int prime = sieve[num] != 0 ? sieve[num] : num;
                dsu.unite(i, n + prime);
                while (num % prime == 0) {
                    num /= prime;
                }
            }
        }

        int root = dsu.find(0);
        for (int i = 1; i < n; i++) {
            if (dsu.find(i) != root) {
                return false;
            }
        }

        return true;
    }
};

// same as DSU + sieve of eratosthenes approach just instead using dfs for same purpose dsu was doing by building a graph
// same complexities as well
class Solution4 {
private:
    void dfs(int node, unordered_map<int, vector<int>>& adj, unordered_set<int>& visited) {
        visited.insert(node);
        for (int neighbor : adj[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor, adj, visited);
            }
        }
    }
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return true;

        if (find(nums.begin(), nums.end(), 1) != nums.end()) {
            return false;
        }

        int mx = *max_element(nums.begin(), nums.end());
        vector<int> sieve(mx + 1, 0);
        for (int p = 2; p * p <= mx; p++) {
            if (sieve[p] == 0) {
                for (int composite = p * p; composite <= mx; composite += p) {
                    sieve[composite] = p;
                }
            }
        }

        unordered_map<int, vector<int>> adj;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (!adj.count(i)) adj[i] = {};

            if (sieve[num] == 0) {
                adj[n + num].push_back(i);
                adj[i].push_back(n + num);
                continue;
            }

            while (num > 1) {
                int prime = (sieve[num] == 0) ? num : sieve[num];
                adj[n + prime].push_back(i);
                adj[i].push_back(n + prime);
                while (num % prime == 0) {
                    num /= prime;
                }
            }
        }

        unordered_set<int> visited;
        dfs(0, adj, visited);
        for (int i = 0; i < n; i++) {
            if (visited.find(i) == visited.end()) {
                return false;
            }
        }

        return true;
    }
};

// here just using sieve of eratosthenes + bfs
// complexity remains the same
class Solution5 {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) return true;

        for (int num : nums) {
            if (num == 1) {
                return false;
            }
        }

        int mx = *max_element(nums.begin(), nums.end());
        vector<int> sieve(mx + 1, 0);
        int p = 2;
        while (p * p <= mx) {
            if (sieve[p] == 0) {
                for (int composite = p * p; composite <= mx; composite += p) {
                    sieve[composite] = p;
                }
            }
            p++;
        }

        unordered_map<int, vector<int>> adj;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (!adj.count(i)) adj[i] = {};
            if (sieve[num] == 0) { // prime number
                adj[i].push_back(n + num);
                adj[n + num].push_back(i);
                continue;
            }

            while (num > 1) {
                int prime = (sieve[num] != 0) ? sieve[num] : num;
                adj[i].push_back(n + prime);
                adj[n + prime].push_back(i);
                while (num % prime == 0) {
                    num /= prime;
                }
            }
        }

        unordered_set<int> visited;
        queue<int> q;
        q.push(0);
        visited.insert(0);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int neighbor : adj[node]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (visited.find(i) == visited.end()) {
                return false;
            }
        }

        return true;
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
