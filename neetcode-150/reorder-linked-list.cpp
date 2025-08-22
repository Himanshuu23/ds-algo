/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    int val;
    Node* next;
    Node() : val(0), next(nullptr) {}
    Node(int x) : val(x), next(nullptr) {}
    Node(int x, Node* next) : val(x), next(next) {}
};

void reorderList(Node* head) {
    Node* slow = head;
    Node* fast = head->next;
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* second = slow->next;
    Node* prev = slow->next = nullptr;
    while (second != nullptr) {
        Node* temp = second->next;
        second->next = prev;
        prev = second;
        second = temp;
    }

    Node* first = head;
    second = prev;
    while (second != nullptr) {
        Node* temp1 = first->next;
        Node* temp2 = second->next;
        first->next = second;
        second->next = temp1;
        first = temp1;
        second = temp2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
