/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

bool hasCycle(ListNode* head) {
    if (!head) return false;

    ListNode* f = head;
    ListNode* s = head;
    bool flag = false;

    while (f && f->next) {
        f = f->next->next;
        s = s->next;
        if (f == s) {
            flag = true;
            break;
        }
    }

    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long t; cin >> t;
    while(t--) {

    }

    return 0;
}
