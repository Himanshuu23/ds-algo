#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
    int key, value;
    Node* prev;
    Node* next;

    Node (int k, int v) {
        key = k;
        value = v;
        prev = next = nullptr;
    }
};
// before first tail node and after last head node keeping NULL nodes
class LRUCache {
    int capacity;
    unordered_map<int, Node*> mp;
    Node* head;
    Node* tail;

    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToFront(Node* node) {
        removeNode(node);
        addToFront(node);
    }

    Node* removeLRU() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

    public:
    LRUCache(int cap) {
        capacity = cap;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (mp.find(key) == mp.end())
            return -1;
        Node* node = mp[key];
        moveToFront(node);
        return node->value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            node->value = value;
            moveToFront(node);
            return;
        }

        if (mp.size() == capacity) {
            Node* lru = removeLRU();
            mp.erase(lru->key);
            delete lru;
        }

        Node* node = new Node(key, value);
        mp[key] = node;
        addToFront(node);
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
