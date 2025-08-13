/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* solve(ListNode* list1, ListNode* list2) {
    if (!list1 && !list2) return nullptr;
    if (!list1) return list2;
    if (!list2) return list1;

    ListNode dummy;
    ListNode* m = &dummy;
    
    while (list1 && list2) {
        if (list1->val <= list2->val) {
            m->next = list1;
            list1 = list1->next;
        } else {
            m->next = list2;
            list2 = list2->next;
        }
        m = m->next;
    }
    
    m->next = list1 ? list1 : list2;

    return dummy.next;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
