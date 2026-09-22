#include <bits/stdc++.h>
using namespace std;

// using dijkstra we find the cheapest cost to go from source to destination but here we also have to track the number of stops (required = k, that is edges = k + 1). So we maintain another distance[city][stops] = bestCost (initially INT_MAX). We push into minHeap (0 - cost, source, -1 -> stops) so when we reach the first station it makes it 0 stops. If more than k stops used or using current city from heap makes larger cost than currentBest than skip
// Time Complexity: if n are number of cities, m are number of flights and K = k + 1 (number of flights, edges limit). Graph has (n.K) states, heap operation takes log(m.K) -> O(n.K + m.K.log(m.K))
// Space Complexity: O(m + n.K + m.K) , heap can hold atmost m.K entries
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> adj(n); // adj[city][cost]
        vector<vector<int>> distance(n, vector<int> (k + 2, INT_MAX)); // since stops are initialized by -1 so we check k+1 and indexing is 0 to k - 1 hence to access k + 1 we make size k + 2 -> distance[city][stops]

        for (auto& flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        distance[src][0] = 0;
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap; // [cost, city, stops]

        minHeap.push({0, src, -1});

        while (!minHeap.empty()) {
            auto [cost, node, stops] = minHeap.top();
            minHeap.pop();

            if (node == dst) return cost;
            if (stops == k || distance[node][stops + 1] < cost) continue;
            for (auto& [neighbor, w] : adj[node]) {
                int nextCost = cost + w;
                int nextStops = stops + 1;
                if (distance[neighbor][nextStops + 1] > nextCost) {
                    distance[neighbor][nextStops + 1] = nextCost;
                    minHeap.push({nextCost, neighbor, nextStops});
                }
            }
        }

        return -1;
    }
};

// bellman ford would be best for this since there we relax based on number of edges count only so there we could just set the limit of the outer loop to be k + 1 and it also relaxes level-wise which is perfect!
// Time complexity: O(n + (m*k)), O(n) where n is number of cities and m are number of flights and k is number of stops
class Solution2 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;

        for (int i = 0; i <= k; i++) {
            vector<int> temporaryPrices = prices;

            for (const auto& flight : flights) {
                int source = flight[0];
                int destination = flight[1];
                int cost = flight[2];

                if (prices[source] == INT_MAX) continue;

                if (prices[source] + cost < temporaryPrices[destination]) {
                    temporaryPrices[destination] = prices[source] + cost;
                }
            }

            prices = temporaryPrices;
        }

        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }
};

// spfa (shortest path faster algorithm) - just for optimizing average case complexity of bellman ford using queue
// O(n*k), O(n + m)
class Solution3 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& flight : flights) {
            adj[flight[0]].push_back({flight[1], flight[2]});
        }

        queue<tuple<int, int, int>> q;
        q.push({0, src, 0});

        while (!q.empty()) {
            auto [cost, node, stops] = q.front();
            q.pop();
            if (stops > k) continue;

            for (auto& [neighbor, nextCost] : adj[node]) {
                if (nextCost + cost < prices[neighbor]) {
                    prices[neighbor] = nextCost + cost;
                    q.push({ nextCost + cost, neighbor, stops + 1});
                }
            }
        }

        return prices[dst] == INT_MAX ? -1 : prices[dst];
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
