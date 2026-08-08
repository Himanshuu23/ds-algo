#include <bits/stdc++.h>
using namespace std;

/*
Problem StatementGiven the head of a singly linked list containing an even number of nodes, pair the $i^{\text{th}}$ node (0-indexed) with the $(n - 1 - i)^{\text{th}}$ node. The sum of a pair is the sum of the values of the two nodes. Return the maximum pair sum among all pairs.Constraint: Must be solved in $\mathcal{O}(1)$ auxiliary space.Sample CaseInput: head = [1, 2, 1, 1, 8, 4]Pairs: $(1, 4) \rightarrow 5$, $(2, 8) \rightarrow 10$, $(1, 1) \rightarrow 2$Output: 10
https://leetcode.com/discuss/post/6225872/amazon-oa-questions-2025-sde2-by-anonymo-qrs8/
*/

class Node {
	public:
	int value;
	Node* next;

	Node (int val) {
		value = val;
		next = nullptr;
	}
};

Node* reverseList(Node* head) {
	Node* previous = nullptr, *current = head, *next = nullptr;
	while (current) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	return previous;
}

int maximumPairSum(Node* head) {
	// finding the middle
	Node* slow = head, *fast = head;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}

	// reversing other half
	Node* second = reverseList(slow);
	Node* first = head;

	int answer = 0;
	while (second) {
		answer = max(answer, first->value + second->value);
		first = first->next;
		second = second->next;
	}

	return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
		int n; cin >> n;
		vector<int> v(n);
		for (int i = 0; i < n; i++) cin >> v[i];
	
		// building the linked list
		Node* head = new Node(v[0]);
		Node* helper = head;
		for (int i = 1; i < n; i++) {
			helper->next = new Node(v[i]);
			helper = helper->next;
		}

		cout << maximumPairSum(head) << '\n';
    }

    return 0;
}
