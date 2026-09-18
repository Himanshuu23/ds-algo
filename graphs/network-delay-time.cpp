#include <bits/stdc++.h>
using namespace std;

// dijkstra, floyd warshall and bellman ford all are relaxation algorithms

// using dfs - O(V + E), O(V + E)
class Solution {
private:
    vector<vector<pair<int, int>>> adj;
    vector<int> distance;

    void dfs(int node, int time) {
        if (time >= distance[node]) return;
        distance[node] = time;
        for (auto& [neighbor, weight] : adj[node]) {
            dfs(neighbor, time + weight);
        }
    }
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        adj.resize(n+1);
        distance.resize(n+1, INT_MAX);

        for (auto& time : times) {
            adj[time[0]].push_back({time[1], time[2]});
        }

        dfs(k, 0);

        int result = *max_element(distance.begin() + 1, distance.end()); // skipping node 0 that is INT_MAX

        return result == INT_MAX ? -1 : result;
    }
};

// using floyd warshall - O(V^3), O(V)
class Solution2 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<int>> distance(n, vector<int> (n, INT_MAX));

        for (int i = 0; i < n; i++) {
            distance[i][i] = 0;
        }

        for (auto& time : times) {
            int u = time[0] - 1, v = time[1] - 1, w = time[2]; // making nodes 0 to n - 1 base so we don't have to handle that node 0 case explicitly
            distance[u][v] = w;
        }

        // using floyd warshall to find all pairs min distances
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (distance[i][k] != INT_MAX && distance[k][j] != INT_MAX)  { // avoiding overflow 
                        distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
                    }
                }
            }
        }

        // now kth node's row -> max value would be the max time it would take to reach from kth node to that destination
        --k; // making it 0 based 
        int result = *max_element(distance[k].begin(), distance[k].end());

        return result == INT_MAX ? -1 : result; 
    }
};

// bellman ford - O(V + E), O(V)
class Solution3 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<int> distance(n, INT_MAX);
        distance[k-1] = 0;

        for (int i = 0; i < n - 1; i++) {
            for (const auto& time : times) {
                int u = time[0] - 1, v = time[1] - 1, w = time[2];
                if (distance[u] != INT_MAX && distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }

        int maxDistance = *max_element(distance.begin(), distance.end());

        return maxDistance == INT_MAX ? -1 : maxDistance;
    }
};

// using spfa (shortest path faster algorithm): optimized bellman ford - instead of trying for all pairs we only try to minimize the pairs who got optimized earlier as well - only those distances are reprocessed which got improved in the past. And also if a node's neighbor's shortest time decreases then that neighbor's neighbor's time might also decrease so we push the neighbor into the queue for processing
// O(V + E) average time , O(V * E) in worst case, O(V + E) space
class Solution4 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& time : times) {
            adj[time[0] - 1].push_back({time[1]- 1, time[2]});
        }

        vector<int> distance(n, INT_MAX);
        distance[k-1] = 0;

        queue<pair<int, int>> q;
        q.push({k-1, 0});

        while (!q.empty()) {
            auto [node, time] = q.front();
            q.pop();
            if (distance[node] < time) continue;
            for (const auto& [neighbor, w] : adj[node]) {
                if (time + w < distance[neighbor]) {
                    distance[neighbor] = time + w;
                    q.push({neighbor, time + w});
                }
            }
        }

        int result = 0;
        for (int time : distance) {
            result = max(result, time);
        }

        return result == INT_MAX ? -1 : result;
    }
};

// using dijkstra - finds shortest distance from one node to all other node (weights must be non-negative) - we always process the node that has the current least time and also once a node is taken out of the priority queue/minHeap its time is finalized - we are always processing the node in order of decreasing distance.
// O(ElogV), O(V + E)
class Solution5 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& time : times) {
            adj[time[0] - 1].push_back({time[1]- 1, time[2]});
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, k-1});

        set<int> visited;
        int time = 0;

        while (!pq.empty()) {
            auto current = pq.top();
            pq.pop();

            int weight = current.first, node = current.second;
            if (visited.count(node)) {
                continue;
            }

            visited.insert(node);
            time = weight;

            for (const auto& next : adj[node]) {
                int neighbor = next.first, neighbor_weight = next.second;
                if (!visited.count(neighbor)) {
                    pq.push({weight + neighbor_weight, neighbor});
                }
            }
        }

        return visited.size() == n ? time : -1;
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
