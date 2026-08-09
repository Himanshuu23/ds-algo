#include<bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// O(n), O(n) - build array of linked list
class Solution1 {
public:
    void reorderList(ListNode* head) {
        if (!head) return;

        vector<ListNode*> nodes;
        ListNode* current = head;
        while (current) {
            nodes.push_back(current);
            current = current->next;
        }
        int i = 0, j = nodes.size() - 1;
        while (i < j) {
            nodes[i]->next = nodes[j];
            i++;
            if (i >= j) break;
            nodes[j]->next = nodes[i];
            j--;
        }

        nodes[i]->next = nullptr;
    }
};

// O(n), O(1) -> find middle, reverse second half, join one from each half
class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* slow = head, *fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        ListNode* second = slow->next;
        slow->next = nullptr;
        ListNode* previous = nullptr;
        while (second) {
            ListNode* next = second->next;
            second->next = previous;
            previous = second;
            second = next;
        }

        ListNode* first = head;
        second = previous;
        while (second) {
            ListNode* next1 = first->next;
            ListNode* next2 = second->next;
            first->next = second;
            second->next = next1;

            first = next1;
            second = next2;
        }
    }
};
