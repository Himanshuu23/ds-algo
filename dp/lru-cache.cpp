#include <bits/stdc++.h>
using namespace std;

class Node {
    Node* prev;
    Node* next;
    Node* head;
    int data;

    Node(int value) {
        data = value;
        prev = NULL;
        next = NULL;
    }

    void insert(int value) {
        Node* node = new Node(value);

        if (!head) {
            head = node;
            return;
        }

        Node* temp = head;
        while (!temp->next)
            temp = temp->next;

        temp->next = node;
        node->next = head;
    }

    void remove(int value) {
        
    }
};

class LRUCache {
    unordered_map<int, int> mp;
    Node dll;

    void put(int value) {
        
    }
};

int main() {
    return 0;
}
