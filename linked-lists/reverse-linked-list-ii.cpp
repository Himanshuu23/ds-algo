#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(0, head); // for each edge cases like reversing the whole list
        
        // reaching node at position left
        ListNode *leftPrevious = dummy, *current = head;
        for (int i = 0; i < left - 1; i++) {
            leftPrevious = current;
            current = current->next;
        }

        // Now current = left, leftPrevious = node before left
        // reverse from left to right -> total links (->) to reverse = right - left + 1 (length of list left to right)
        ListNode* previous = nullptr;
        for (int i = 0; i < (right - left + 1); i++) {
            ListNode* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        leftPrevious->next->next = current; // pointing original node at left to next of original node at right
        leftPrevious->next = previous; // pointing original previousNode -> next to new node at left position 
        
        return dummy->next; 
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
    }

    return 0;
}
