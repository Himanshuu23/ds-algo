#include <bits/stdc++.h>
using namespace std;

// Using vector - O(k) -> space, O(1) -> per operations
class MyCircularQueue {
    vector<int> v;
    int front, rear, size, capacity;
public:
    MyCircularQueue(int k) {
        front = -1;
        rear = -1;
        capacity = k;
        size = 0;
        v.resize(k);
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;

        if (isEmpty()) {
            rear = front = 0;
        } else {
            rear = (rear + 1) % capacity;
        }

        v[rear] = value;
        size++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;

        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % capacity;
        }

        size--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return v[front];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return v[rear];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};

// using singly linked list -> same complexities (we can also use doubly linked list)
class MyCircularQueue2 {
    private:
        struct Node {
            int value;
            Node* next;
            Node(int data) : value(data), next(nullptr) {}
        };
        int space;
        Node* left, *right;
public:
    MyCircularQueue2(int k) {
        space = k;
        left = new Node(0);
        right = left;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;

        Node* current = new Node(value);
        if (isEmpty()) {
            left->next = current;
            right = current;
        } else {
            right->next = current;
            right = current;
        }

        space--;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;

        Node* temp = left->next;
        left->next = left->next->next;
        delete temp;
        if (!left->next) {
            right = left;
        }

        space++;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;

        return left->next->value;
    }
    
    int Rear() {
        if (isEmpty()) return -1;

        return right->value;
    }
    
    bool isEmpty() {
        return left->next == nullptr; 
    }
    
    bool isFull() {
        return space == 0; 
    }

    ~MyCircularQueue2() {
        while (!isEmpty()) deQueue();
        delete left;
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
