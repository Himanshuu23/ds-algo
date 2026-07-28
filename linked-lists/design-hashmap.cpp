class MyHashMap {
	private:
		struct Node {
			int key, value;
			Node* next;

			Node(int key = -1, int value = -1, Node* next = nullptr) : key(key), value(value), next(next) {}
		};

		vector<Node*> map;
		int hash(int key) {
			return key % map.size();
		}

	public:
		MyHashMap() {
			map.resize(1000);
			for (auto& bucket : map) {
				bucket = new Node(0);
			}
		}

		void put(int key, int value) {
			Node* current = map[hash(key)];
			while (current->next) {
				if (current->next->key == key) {
					current->next->value = value;
					return;
				}
				current = current->next;
			}
			current->next = new Node(key, value);
		}

		int get(int key) {
			Node* current = map[hash(key)];
			while (current->next) {
				if (current->next->key == key) return current->next->value;
				current = current->next;
			}
			return -1;
		}

		void remove(int key) {
			Node* current = map[hash(key)];
			while (current->next) {
				if (current->next->key == key) {
					Node* temp = current->next;
					current->next = temp->next;
					delete temp;
					return;
				}
				current = current->next;
			}
		}
};
