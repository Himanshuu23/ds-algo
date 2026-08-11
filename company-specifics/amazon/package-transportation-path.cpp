#include <bits/stdc++.h>
using namespace std;

/*
You are given a list of dependencies between packages represented as directed edges, along with a Source package and a Destination package.
Rules & Definitions
Each package is represented by a unique string.
A dependency PackageX -> PackageY means that transporting PackageX unlocks or leads to PackageY.
You need to find a valid directed path of packages starting at Source and ending at Destination.
Task
Find and return the sequence of packages to transport from Source to Destination as a formatted string joined by ->. If no valid path exists, return an empty string "".
Example
Input:
dependencies = [("PackageA", "PackageB"), ("PackageB", "PackageC"), ("PackageB", "PackageD"), ("PackageD", "PackageH"), ("PackageH", "PackageG")]
Source = "PackageA"
Destination = "PackageG"
Output:
"PackageA -> PackageB -> PackageD -> PackageH -> PackageG"
Link - https://takeuforward.org/interview-experience/amazon-interview-experience-sde-intern-set-5
*/

// use bfs -> track current path, make map for dependencies
// O(M*N) where M -> size of dependencies array and N -> maximum packages we can go to through a package
string findPackagePath(vector<pair<string, string>>& dependencies, string source, string destination) {
    unordered_map<string, vector<string>> graph;
    for (auto& dependency : dependencies) {
        graph[dependency.first].push_back(dependency.second);
    }
    
    queue<string> q;
    unordered_set<string> visited;
    unordered_map<string, string> parent;

    q.push(source);
    visited.insert(source);

    bool found = false;
    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == destination) {
            found = true;
            break;
        }

        for (string neighbour : graph[current]) {
            if (!visited.count(neighbour)) {
                visited.insert(neighbour);
                parent[neighbour] = current;
                q.push(neighbour);
            }
        }
    }

    if (!found) {
        return "";
    }

    vector<string> path;
    string current = destination;
    while (current != source) {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(source);
    reverse(path.begin(), path.end());

    string result = path[0];
    for (int i = 1; i < (int)path.size(); i++) {
        result += " -> " + path[i]; 
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        vector<pair<string, string>> dependencies = {
            {"PackageA", "PackageB"},
            {"PackageB", "PackageC"},
            {"PackageB", "PackageD"},
            {"PackageD", "PackageH"},
            {"PackageH", "PackageG"}
        };

        cout << findPackagePath(dependencies, "PackageA", "PackageG") << '\n';
    }

    return 0;
}
