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

    node (int val) {
        data = val;
        next = NULL;
    }
};

// O(L), O(1), L -> lenth of the linked list
node* solve2(node* head, int n) {
    node* dummy = new node(-1);
    dummy->next = head;
    node* current = head;
    int length = 0;
    while (current) {
        current = current->next;
        ++length;
    }

    length -= n;
    current = dummy; // handles when head is to be deleted
    while (length-- && current) {
        current = current->next;
    }
    node* toDelete = current->next;
    current->next = toDelete->next;
    delete toDelete;
    return dummy->next;
}

// O(L), O(1), L -> lenth of the linked list - better since single pass
void solve(node* &head, int n) {
    node* dummy = new node(0);
    dummy->next = head;
    node* fast = dummy;
    node* slow = dummy;

    for (int i = 0; i < n; i++) fast = fast->next;
    while(fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    node* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    head = dummy->next;
    delete dummy;
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
        int n; cin >> n;
        node* head = new node(0);
        head->next = new node(1);
        head->next->next = new node(2);
        display(head);
        solve(head, n);
        display(head);
    }

    return 0;
}
