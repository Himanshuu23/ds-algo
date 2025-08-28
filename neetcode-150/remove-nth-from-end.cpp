/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {};
};

ListNode* solve(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* fast = dummy;
    ListNode* slow = dummy;
    for (int i = 0; i < n && fast->next; i++) fast = fast->next;
    while(fast->next) {
        slow = slow->next;
        fast = fast->next;
    }

    ListNode* toDel = slow->next;
    slow->next = slow->next->next;
    delete toDel;

    head = dummy->next;
    delete dummy;
    return head;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
