#include <bits/stdc++.h>
using namespace std;

/*
You are given an array deliveryLogs of size $n$, where deliveryLogs[i] represents the number of items delivered in the $i^{\text{th}}$ log. You are also given an even integer $k$, representing the total number of warehouses available.You need to distribute deliveries across at most $k$ warehouses subject to the following rules:No Mixing: Each warehouse can store items from at most one delivery log. (Items from different logs cannot share a warehouse, but items from a single log can be split across multiple warehouses).Compromised Warehouses: After distribution, the $\frac{k}{2}$ warehouses with the largest number of items will be compromised.Safe Warehouses: The remaining $\frac{k}{2}$ warehouses with the smallest number of items are safe, and only their items count toward the total secure deliveries.Find the maximum total number of secure deliveries you can save in the $\frac{k}{2}$ safe warehouses.Input Formatn: An integer representing the size of deliveryLogs.deliveryLogs: An array of $n$ integers.k: An even integer representing the total number of available warehouses.Output FormatReturn a single integer representing the maximum number of secure deliveries.ExampleInput:n = 4deliveryLogs = [3, 5, 9, 6]k = 4 ($\frac{k}{2} = 2$)Output: 9Explanation:Split the $3^{\text{rd}}$ log (9) into two warehouses with capacities 4 and 5.Store logs in 4 warehouses: [5, 4, 5, 6] (ignoring the first log 3).The 2 largest warehouses (6 and 5) are compromised.The 2 remaining safe warehouses hold 4 + 5 = 9 items.
*/

// to maximize the total deliveries in the k/2 safe warehouses we want to cap the compromised warehouses at a value of X. The K/2 compromised will each get atleast X items, remaining K/2 safe warehouses will get as close to X or either full X or largest remaining sized. So first binary search -> to find Xmax using which we can form atleast K/2 full chunks of size X - these can be used to fill up the compromised k/2 warehouses. getSafeSum() -> for chosen X put k/2 chunks of X in compromised houses. Fill safe, extra chunks of size X beyond k/2 go directly to safe ones. Also if we still need more warehouses to fill the k/2 safe slots then we take the remainders -> largest remaining after taking all X sized chunks of each. Now second binary search to find the optimal X -> getSafeSum() is roughly unimodal that is increases to peak and then drops. So we use another binary on X which ranges from 1 to Xmax to find such value of X that maximizes getSafeSum(X) - coz if we use X that is too large then we won't have enough items to fill the k/2 sacrified warehouses or if its too small then sacrifical takes very little but safe houses also end up holding very small chunks since we give them X at first only hence all k/2 safe houses filled with small values
// Complexity - O(Nlog^2(max(logs))), O(N)

// helper function to find the total safe deliveries for a particular X
long long getSafeSum(vector<int>& deliveryLogs, int k, long long X) {
    long long total_full_chunks = 0;
    for (int d : deliveryLogs) {
        total_full_chunks += d / X;
    }

    long long target_compromised = k / 2;

    // not enough full chunks to fill compromised warehouses
    if (total_full_chunks < target_compromised) return -1;
    
    // filling as many remaining safe houses with X only
    long long safe_full_chunks = min((long long)k / 2, total_full_chunks - target_compromised);
    long long current_safe_sum = safe_full_chunks * X;
    long long needed_safe = (k / 2) - safe_full_chunks;

    // filling remaining safe houses with max remaining values 
    if (needed_safe > 0) {
        vector<int> remainders;
        for (int d : deliveryLogs) {
            int remainder = d % X;
            if (remainder > 0) {
                remainders.push_back(remainder);
            }
        }

        sort(remainders.rbegin(), remainders.rend());

        long long take = min((long long)remainders.size(), needed_safe);
        for (int i = 0; i < take; i++) {
            current_safe_sum += remainders[i];
        }
    }

    return current_safe_sum;
} 

int secureMaximumDeliveries(vector<int>& deliveryLogs, int k) {
    // binary search to find the Xmax
    long long low = 1, high = 0;
    for (int d : deliveryLogs) {
        high = max(high, (long long)d);
    }

    long long X_max = 0;
    while (low <= high) {
        long long middle = low + (high - low) / 2;
        long long total_full = 0;
        for (int d : deliveryLogs) {
            total_full += d / middle;
        }
        if (total_full >= k / 2) {
            X_max = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    if (X_max == 0) return 0;

    // Binary search on [1, X_max] to find the safe deliveries
    low = 1, high = X_max;
    long long max_safe_deliveries = 0;

    while (low <= high) {
        long long middle = low + (high - low) / 2;
        long long f_middle = getSafeSum(deliveryLogs, k, middle);
        long long f_next = (middle + 1 <= X_max) ? getSafeSum(deliveryLogs, k, middle + 1) : -1;

        max_safe_deliveries = max(max_safe_deliveries, f_middle);
        if (f_next != -1) {
            max_safe_deliveries = max(max_safe_deliveries, f_next);
        }

        // move towards the hill's peak
        if (f_next >= f_middle) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    return (int)max_safe_deliveries;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, k; cin >> n >> k;
        vector<int> deliveryLogs(n);
        for (int& x : deliveryLogs) {
            cin >> x;
        }
        cout << secureMaximumDeliveries(deliveryLogs, k) << '\n';
    }

    return 0;
}
