#include <bits/stdc++.h>
using namespace std;

// brute force: get - O(1), put - O(n), space - O(n)
class LFUCache2 {
    struct Node {
        int value, frequency, timestamp;
        Node(int v, int f, int t) : value(v), frequency(f), timestamp(t) {}
    };

    int capacity, timestamp;
    unordered_map<int, Node*> cache;
public:
    LFUCache2(int capacity) : capacity(capacity), timestamp(0) {}
    
    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;

        cache[key]->frequency++;
        cache[key]->timestamp = ++timestamp;
        return cache[key]->value;
    }
    
    void put(int key, int value) {
        if (capacity <= 0) return;

        timestamp++;
        if (cache.find(key) != cache.end()) {
            cache[key]->value = value;
            cache[key]->frequency++;
            cache[key]->timestamp = timestamp;
            return;
        }

        if (cache.size() >= capacity) {
            int minFrequency = INT_MAX, minTimestamp = INT_MAX, lfuKey = -1;

            for (const auto& [k, node] : cache) {
                if (node->frequency < minFrequency || (node->frequency == minFrequency && node->timestamp < minTimestamp)) {
                    minFrequency = node->frequency;
                    minTimestamp = node->timestamp;
                    lfuKey = k;
                }
            }

            delete cache[lfuKey];
            cache.erase(lfuKey);
        }

        cache[key] = new Node(value, 1, timestamp);
    }
};

// using doubly linked list
// O(1) both operations, space complexity - O(n)
class LFUCache {
    struct Node {
        int key, value, frequency;
        Node* previous;
        Node* next;

        Node(int key, int value) : key(key), value(value), frequency(1), previous(nullptr), next(nullptr) {}
    };

    struct LinkedList {
        int size;
        Node* left, *right;

        LinkedList() {
            left = new Node(0, 0);
            right = new Node(0, 0);
            left->next = right;
            right->previous = left;
            size = 0;
        }

        ~LinkedList() {
            delete left;
            delete right;
        }

        int length() {
            return size;
        }

        void pushRight(Node* node) {
            Node* previous = right->previous;
            previous->next = node;
            node->previous = previous;
            node->next = right;
            right->previous = node;
            size++;
        }

        void pop(Node* node) {
            Node* previous = node->previous;
            Node* next = node->next;
            previous->next = next;
            next->previous = previous;
            node->previous = nullptr;
            node->next = previous;
            size--; 
        }

        Node* popLeft() {
            Node* node = left->next;
            pop(node);
            return node;
        }

    };

    int capacity;
    int lfuCount;
    unordered_map<int, Node*> nodeMap; // Map of key->node
    unordered_map<int, LinkedList*> listMap; // Map of frequency->linked list
    
    void counter(Node* node) {
        int count = node->frequency;
        listMap[count]->pop(node);

        if (count == lfuCount && listMap[count]->length() == 0) {
            lfuCount++;
        }

        node->frequency++;
        if (!listMap.count(node->frequency)) {
            listMap[node->frequency] = new LinkedList();
        }
        listMap[node->frequency]->pushRight(node);
    }

public:
    LFUCache(int capacity) : capacity(capacity), lfuCount(0) {}
    
    ~LFUCache() {
        for (auto& pair : nodeMap) {
            delete pair.second;
        }

        for (auto& pair : listMap) {
            delete pair.second;
        }
    }

    int get(int key) {
        if (nodeMap.find(key) == nodeMap.end()) {
            return -1;
        }

        Node* node = nodeMap[key];
        counter(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }

        if (nodeMap.find(key) != nodeMap.end()) {
            Node* node = nodeMap[key];
            node->value = value;
            counter(node);
            return;
        }

        if (nodeMap.size() == capacity) {
            Node* toRemove = listMap[lfuCount]->popLeft();
            nodeMap.erase(toRemove->key);
            delete toRemove;
        }

        Node* node = new Node(key, value);
        nodeMap[key] = node;
        if (!listMap.count(1)) {
            listMap[1] = new LinkedList();
        }

        listMap[1]->pushRight(node);
        lfuCount = 1;
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
