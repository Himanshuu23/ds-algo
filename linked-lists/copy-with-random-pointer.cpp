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


node* copy(node* head) { // simpler approach using hash map
    node* temp = head;
    unordered_map<node*, node*> mp;
    while (temp) {
        mp[temp] = new node(temp->data);
        temp = temp->next;
    }
    temp = head;
    node* newHead = mp[temp], *dummy = new node(-1);
    dummy->next = mp[temp];
    while (temp) {
        newHead->next = temp->next ? mp[temp->next] : nullptr; // to avoid inserting NULL (last node into map) - works but garbage
        newHead->random = temp->random ? mp[temp->random] : nullptr;
        temp = temp->next;
        newHead = newHead->next;
    }

    return dummy->next;
}


node* solve(node* &head) {
    if (!head) return nullptr;

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
