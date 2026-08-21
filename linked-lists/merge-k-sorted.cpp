/*
    author: Himanshuu23
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class ListNode {
    public:
        int value;
        ListNode* next;

        ListNode(int value) {
            this->value = value;
            next = NULL;
        }
};

// brute force: merge all together and sort - nlogn 
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> nodes;
        for (ListNode* lst : lists) {
            while (lst) {
                nodes.push_back(lst->value);
                lst = lst->next;
            }
        }
        sort(nodes.begin(), nodes.end());
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        for (int node : nodes) {
            current->next = new ListNode(node);
            current = current->next;
        }
        return dummy->next;
    }
};

// using min heap - nlogk where k is total number of lists, O(k)
class Solution2 {
    struct compare {
        bool operator() (ListNode* a, ListNode* b) {
            return a->value > b->value;
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> minHeap;

        for (auto lst : lists) {
            if (lst) {
                minHeap.push(lst);
            }
        }

        ListNode* dummy = new ListNode(0);
        ListNode* tail = dummy;

        while (!minHeap.empty()) {
            ListNode* smallest = minHeap.top();
            minHeap.pop();

            tail->next = smallest;
            tail = tail->next;

            if (smallest->next) {
                minHeap.push(smallest->next);
            }
        }

        return dummy->next;
    }
};

// using divide and conquer - nlogk
class Solution3 {
    ListNode* mergeTwoSortedLists(ListNode* &h1, ListNode* &h2) {
        ListNode* dummy = new ListNode(-1);
        ListNode* current = dummy;

        while (h1 && h2) {
            if (h1->value < h2->value) {
                current->next = h1;
                h1 = h1->next;
            } else {
                current->next = h2;
                h2 = h2->next;
            }
            current = current->next;
        }

        current->next = h1 ? h1 : h2;

        return dummy->next;              
    }

    ListNode* mergeK(vector<ListNode*>& lists, int start, int end) {
        if (start > end) return NULL;
        if (start == end) return lists[start];

        int middle = (start + end) / 2;
        ListNode* l1 = mergeK(lists, start, middle);
        ListNode* l2 = mergeK(lists, middle+1, end);

        return mergeTwoSortedLists(l1, l2);
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return mergeK(lists, 0, lists.size() - 1);
    }
};

void display(ListNode* head) {
    while (head) {
        cout << head->value << "->";
        head = head->next;
    }
    cout << "NULL\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ListNode*> lists;
    int val = 0;
    long t;
    cin >> t;

    while (t--) {
        ListNode* head = new ListNode(val++);
        ListNode* head1 = new ListNode(val++);
        ListNode* curr = head;
        ListNode* curr2 = head1;

        for (int i = 0; i < 2; ++i) {
            curr->next = new ListNode(val++);
            curr2->next = new ListNode(val++);
            curr = curr->next;
            curr2 = curr2->next;
        }

        lists.push_back(head);
        lists.push_back(head1);
    }

    // node* sol = solve(lists);
    ListNode* sol2 = mergeKList(lists, 0, lists.size() - 1);
    //display(sol);
    display(sol2);
    return 0;
}
