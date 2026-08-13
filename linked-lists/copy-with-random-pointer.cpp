/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class node {
    public:
    int data;
    node* next;
    node* random;

    node (int val) {
        data = val;
        next = NULL;
        random = NULL;
    }
};


// O(N), O(N) - using hashmap
node* copy(node* head) {
    if (!head) return nullptr;

    unordered_map<node*, node*> mp;
    node* temp = head;
    while (temp) {
        mp[temp] = new node(temp->data);
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


node* solve(node* &head) {
    if (!head) return nullptr;

    // making A->B->C to A->A'->B->B'->C->C'
    node* curr = head;
    while(curr) {
        node* copy = new node(curr->data);
        copy->next = curr->next;
        curr->next = copy;
        curr = copy->next;
    }

    curr = head;
    while(curr) {
        if (curr->random) curr->next->random = curr->random->next;
        curr = curr->next->next;
    }

    // getting back cloned nodes
    curr = head;
    node* newhead = head->next;
    while(curr) {
        node* copy = curr->next;
        curr->next = copy->next;
        if (copy->next)
            copy->next = copy->next->next;
        curr = curr->next;
    }

    return newhead;
}

void display(node* &head) {
    node* temp = head;
    while (temp != NULL) {
        cout << temp->data << "->";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {
        node* head = new node(7);
        head->next = new node(13);
        head->next->random = head;
        head->next->next = new node(11);
        head->next->next->random = head->next->next->next;
        head->next->next->next = new node(10);
        display(head);
        node* newhead = solve(head);
        display(newhead);
    }

    return 0;
}
