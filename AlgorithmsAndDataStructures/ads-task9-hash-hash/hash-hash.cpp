#include <iostream>
#include <fstream> 

class HashTable {
	class Node {
	public:
		int value;
		Node* next;
		Node(int value_) : value(value_), next(nullptr) {}
		~Node() {
			delete next;
		}
	};
	class List {
	public:
		int length;
		Node* head;
		List() {
			length = 0;
			head = nullptr;
		}
		void add(int new_el) {
			Node* new_head = new Node(new_el);
			new_head->next = head;
			head = new_head;
			++length;
		}
		~List() { delete head; };
	};

	int capacity;
	List* arr;
	int length;
	float fill_factor;

	class Iterator {
	public:
		Node* head;
		int input_val;
		Iterator(Node* head_, int input_val_) : head(head_), input_val(input_val_) {};
	};
	Iterator begin() {
		int i = 0;
		while (arr[i].head == nullptr) {
			++i;
			if (i > capacity) {
				--i;
				break;
			}
		}
		return Iterator(arr[i].head, i);
	}
	Iterator next(Iterator itr) {
		if (itr.head->next != nullptr) {
			int i = itr.input_val;
			do {
				++i;
				if (i > capacity) {
					--i;
					break;
				}
			} while (arr[i].head == nullptr);
			return Iterator(arr[i].head, i);
		}
		return Iterator(itr.head->next, itr.input_val);
	}

	int hush_func(int val) const {
		if (val < 0) {
			val *= -1;
		}
		return val % capacity;
	}
	void expansion() {
		capacity *= 2;
		Iterator itr = begin();
		List* new_arr = new List[capacity];
		while (itr.head != nullptr) {
			new_arr[hush_func(itr.head->value)].add(itr.head->value);
			itr = next(itr);
		}
		delete[] arr;
		arr = new_arr;
	}
public:
	HashTable(float fill_factor_, int capacity_) : fill_factor(fill_factor_), capacity(capacity_) {
		length = 0;
		arr = new List[capacity];
	};
	~HashTable() {
		delete[] arr;
	};
	int add(int value) {
		if (float(length) / float(capacity) > fill_factor) {
			expansion();
		}
		int hash = hush_func(value);
		arr[hash].add(value);
		++length;
		return value;
	}
	bool find(int value) {
		int hush = hush_func(value);
		Node* curr = arr[hush].head;
		while (curr != nullptr) {
			if (curr->value == value) {
				return true;
			}
			curr = curr->next;
		}
		return false;
	}
	bool del(int value) {
		int hush = hush_func(value);
		Node* curr = arr[hush].head;
		Node* past = arr[hush].head;
		while (curr != nullptr) {
			if (curr->value == value) {
				if (arr[hush].length == 1) {
					delete curr;
					arr[hush].head = nullptr;
				}
				else {
					past->next = curr->next;
					curr->next = nullptr;
					delete curr;
					--length;
				}
				return true;
			}
			past = curr;
			curr = curr->next;
		}
		return false;
	}
};


int main(int argc, char* argv[]) {
	std::ofstream out(argv[2]);
	std::ifstream in(argv[1]);
	int quantity_op = 1;
	in >> quantity_op;
	int quantity_true = 0;
	int quantity_false = 0;
	int index = 0;
	HashTable hs = HashTable(1.0, 1103);
	int i = 0;
	while (i < quantity_op) {
		char curr_op;
		in >> curr_op;
		if (curr_op == '+') {
			int number = 0;
			in >> number;
			hs.add(number);
		}
		else if (curr_op == '-') {
			int number = 0;
			in >> number;
			hs.del(number);
		}
		else if (curr_op == '?') {
			int number = 0;
			in >> number;
			if (hs.find(number)) {
				out.write("true\n",5);
			}
			else {
				out.write("false\n", 6);
			}
			++index;
		}
		++i;
	}
	in.close();
	out.close();
	return 0;
}
