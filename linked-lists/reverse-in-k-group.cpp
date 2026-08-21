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

    node (int value) {
        data = value;
        next = NULL;
    }
};

// O(n), O(n/k)
class Solution {
public:
    node* reverseKGroup(node* head, int k) {
        node* current = head;
        int group = 0;
        while (current != nullptr && group < k) {
            current = current->next;
            group++;
        }

        if (group == k) {
            current = reverseKGroup(current, k);
            // same as reversing the list now just current = head and previous = current
            while (group--) {
                node* next = head->next;
                head->next = current;
                current = head;
                head = next;
            }

            head = current;
        }

        return head;
    }
};

// O(n), O(1)
node* reverseKGroup(node* head, int k) {
    if (!head || k == 1) return head;

    node dummy(0); // to handle edge cases
    dummy.next = head;
    node* prev = &dummy; // points to last reversed's tail so we can combine with next parts head

    while (true) {
        node* curr = prev;
        for (int i = 0; i < k && curr; ++i) curr = curr->next;
        if (!curr) break;

        node* tail = prev->next; // points to node that becomes tail of current group
        node* next = curr->next; // points to next node of this group - to connect new tail with that

        node* p = tail;
        node* q = p->next;

        while (q != next) {
            node* temp = q->next;
            q->next = p;
            p = q;
            q = temp;
        }

        prev->next = curr; // connecting new tail with next node
        tail->next = next; // connecting previous group's tail to new head
        prev = tail; // updating tail to head of recently reversed node
    }

    return dummy.next;
}

void display(node* &head) {
    node* temp = head;
    while (temp) {
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
        node* head = new node(0);
        head->next = new node(1);
        head->next->next = new node(2);
        head->next->next->next = new node(3);
        head->next->next->next->next = new node(4);
        display(head);
        head = reverseKGroup(head, 2);
        display(head);
    }

    return 0;
}
