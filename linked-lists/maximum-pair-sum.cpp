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
class Solution {
public:
ListNode* reverseList(ListNode* head) {
	ListNode* previous = nullptr, *current = head, *next = nullptr;
	while (current) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	return previous;
}
    int pairSum(ListNode* head) {
        ListNode* slow = head, *fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	ListNode* second = reverseList(slow);
	ListNode* first = head;

	int answer = 0;
	while (second) {
		answer = max(answer, first->val + second->val);
		first = first->next;
		second = second->next;
	}

	return answer;

    }
};
