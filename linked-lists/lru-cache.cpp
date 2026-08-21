#include<bits/stdc++.h>
using namespace std;

// brute force, get and put -> O(n) - keeping recent value at the end of the array
class LRUCache2 {
private:
    vector<pair<int, int>> cache;        
    int capacity;
public:
    LRUCache2(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].first == key) {
                pair<int, int> temp = cache[i];
                cache.erase(cache.begin() + i);
                cache.push_back(temp);
                return temp.second;
            }
        }

        return -1;
    }
    
    void put(int key, int value) {
        for (int i = 0; i < cache.size(); i++) {
            if (cache[i].first == key) {
                cache.erase(cache.begin() + i);
                cache.push_back({key, value});
                return;
            }
        }
        if (cache.size() == capacity) {
            cache.erase(cache.begin());
        }
        cache.push_back({key, value});
    }
};

// using doubly linked list - O(1) both operations keeping right as most recent, last as least recent value
class Node {
    public:
    int key, value;
    Node* previous;
    Node* next;

    Node(int k, int v) : key(k), value(v), previous(nullptr), next(nullptr) {};
};

class LRUCache {
    int capacity;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void remove(Node* node) {
        Node* previous = node->previous;
        Node* next = node->next;
        previous->next = next;
        next->previous = previous;
    }

    void insert(Node* node) {
        Node* previous = tail->previous;
        previous->next = node;
        node->previous = previous;
        node->next = tail;
        tail->previous = node;
    }

    public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        cache.clear();
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->previous = head;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            insert(node);
            return node->value;
        }

        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);
        }
        Node* newNode = new Node(key, value);
        cache[key] = newNode;
        insert(newNode);

        if (cache.size() > capacity) {
            Node* lru = head->next;
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
    }
};

int main() {
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << endl;
    cache.put(3, 30);
    cout << cache.get(2) << endl;
    cache.put(4, 40);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;
}
