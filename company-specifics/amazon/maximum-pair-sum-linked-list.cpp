#include <bits/stdc++.h>
using namespace std;

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
