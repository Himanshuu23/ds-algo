#include <bits/stdc++.h>
using namespace std;

// same as LeetCode 
// Link - https://www.linkedin.com/pulse/amazon-interview-experience-sde-i-6-months-internship-bedi/

class Node {
    public:
        int value;
        Node* next, *random;
        
        Node(int value) : value(value), next(nullptr), random(nullptr) {}
};

// O(N), O(N) - using hashmap
Node* solve(Node* head) {
    if (!head) return nullptr;

    unordered_map<Node*, Node*> mp;
    Node* temp = head;
    while (temp) {
        mp[temp] = new Node(temp->value);
        temp = temp->next;
    }
    temp = head;
    while (temp) {
        mp[temp]->next = mp[temp->next];
        mp[temp]->random = mp[temp->random];
        temp = temp->next;
    }

    return mp[head];
}

// O(N), O(1)
Node* solve2(Node* head) {
    if (!head) return nullptr;

    Node* current = head;
    while (current) {
        Node* copy = new Node(current->value);
        copy->next = current->next;
        current->next = copy;
        current = copy->next;
    }

    current = head;
    while (current) {
        if (current->random) {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    current = head;
    Node* newHead = current->next;
    while (current) {
        Node* copy = current->next;
        current->next = copy->next;
        if (copy->next) {
            copy->next = copy->next->next;
        }
        current = current->next;
    }

    return newHead;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
