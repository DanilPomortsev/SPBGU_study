#include <iostream>
#include <fstream>


template<typename T>
class Node {
public:
	Node<T>* next_node;
	T content;
	T min;
	T max;

	Node() {}
	Node(T content_, T min_, T max_) : content(content_), next_node(nullptr), min(min_), max(max_) {}
	~Node() {

	}

};

template<typename T>
class StackMinMax {
	int lenght;
	Node<T>* first;
	static T min(T arg1, T arg2) {
		if (arg1 < arg2) {
			return arg1;
		}
		return arg2;
	}

	static T max(T arg1, T arg2) {
		if (arg1 > arg2) {
			return arg1;
		}
		return arg2;
	}
public:
	StackMinMax() {
		lenght = 0;
		first = nullptr;
	}

	void push(T element) {
		Node<T>* curr_top = first;
		if (curr_top != nullptr) {
			T curr_min = min(element, curr_top->min);
			T curr_max = max(element, curr_top->max);
			Node<T>* new_node = new Node<T>(element, curr_min, curr_max);
			new_node->next_node = first;
			first = new_node;
		}
		else {
			Node<T>* new_node = new Node<T>(element, element, element);
			new_node->next_node = first;
			first = new_node;
		}
		++lenght;
	}

	void pop() {
		Node<T>* result = first;
		if (first != nullptr) {
			first = first->next_node;
		}
		--lenght;
		delete result;
	}

	Node<T>* peek() {
		return first;
	}

	int size() {
		return lenght;
	}

	int razn() {
		if (lenght < 2) {
			return 0;
		}
		return first->max - first->min;
	}

	~StackMinMax() {
		while (first != nullptr) {
			Node<T>* next = first->next_node;
			delete first;
			first = next;
		}
	}
};

template<typename T>
class QueueMinMax {
	StackMinMax<T> push_stack;
	StackMinMax<T> pop_stack;
public:
	QueueMinMax() {

	}
	void push_back(T element) {
		push_stack.push(element);
	}
	void pop_front() {
		if (pop_stack.size() == 0) {
			while (push_stack.size() != 0) {
				pop_stack.push(push_stack.peek()->content);
				push_stack.pop();
			}
		}
		pop_stack.pop();
	}
	int max_min() {
		int razn_pop = pop_stack.razn();
		int razn_push = push_stack.razn();
		if (razn_push > razn_pop) {
			return razn_push;
		}
		return razn_pop;
	}
	~QueueMinMax() {
	}

};

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	int quantity_op = 1;
	in >> quantity_op;
	QueueMinMax<int> queue;
	for (int i = 0; i < quantity_op; ++i) {
		char curr_op = '0';
		in >> curr_op;
		if (curr_op == '+') {
			int number = 0;
			in >> number;
			queue.push_back(number);
		}
		else if (curr_op == '-') {
			queue.pop_front();
		}
		else if (curr_op == '?') {
			out << queue.max_min() << std::endl;
		}
	}
	in.close();
	out.close();
	return 0;
}
