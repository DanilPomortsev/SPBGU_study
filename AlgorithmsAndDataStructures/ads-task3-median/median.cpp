#include <iostream>
#include <fstream>

template<typename T>
class Node {
public:
	Node<T>* next_node;
	T content;

	Node() {}
	Node(T content_) : content(content_), next_node(nullptr) {}
	~Node() {

	}

};

template<typename T>
class Stack {
	int lenght;
	Node<T>* first;
public:
	Stack() {
		lenght = 0;
		first = nullptr;
	}

	void push(T element) {
		Node<T>* curr_top = first;
		if (curr_top != nullptr) {
			Node<T>* new_node = new Node<T>(element);
			new_node->next_node = first;
			first = new_node;
		}
		else {
			Node<T>* new_node = new Node<T>(element);
			new_node->next_node = first;
			first = new_node;
		}
		++lenght;
	}

	T pop() {
		Node<T>* result = first;
		if (first != nullptr) {
			first = first->next_node;
		}
		T result_content = result->content;
		--lenght;
		delete result;
		return result_content;
		
	}

	Node<T>* peek() {
		return first;
	}

	int size() {
		return lenght;
	}

	~Stack() {
		while (first != nullptr) {
			Node<T>* next = first->next_node;
			delete first;
			first = next;
		}
	}
};

class Para {
public:
	int start;
	int end;
	~Para() {};
	Para(int start_, int end_) : start(start_), end(end_) {}
};

class Student {
public:
	double mark;
	int id;
	Student(double mark_, int id_) : mark(mark_), id(id_) {};
	Student(){};
	~Student() {};

	friend bool operator <(Student const& c1, Student const& c2) {
		return c1.mark < c2.mark;
	}
	friend bool operator >(Student const& c1, Student const& c2) {
		return c1.mark > c2.mark;
	}
	friend bool operator == (Student const& c1, Student const& c2) {
		return c1.mark == c2.mark;
	}
};


template<typename T>
void quick_sort(int len, T* arr) {
	Stack<Para> stk;
	stk.push(Para(0, len-1));
	while (stk.size() != 0) {
		Para curr_borders = stk.pop();
		if (curr_borders.start >= curr_borders.end) {
			continue;
		}
		T mediana_val = arr[curr_borders.start + (curr_borders.end - curr_borders.start) / 2];
		int left_ptr = curr_borders.start;
		int right_ptr = curr_borders.end;
		do {
			while (arr[left_ptr] < mediana_val) {
				++left_ptr;
			}
			while (arr[right_ptr] > mediana_val) {
				--right_ptr;
			}
			if (left_ptr <= right_ptr) {
				T tmp = arr[left_ptr];
				arr[left_ptr] = arr[right_ptr];
				arr[right_ptr] = tmp;
				++left_ptr;
				--right_ptr;
			}
		} while (left_ptr < right_ptr);
		stk.push(Para(curr_borders.start, right_ptr));
		stk.push(Para(left_ptr, curr_borders.end));
	}
}

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	int quantity_st = 1;
	in >> quantity_st;
	Student* arr = new Student[quantity_st];
	for (int i = 1; i < quantity_st+1; ++i) {
		double curr_mark;
		in >> curr_mark;
		arr[i-1] = Student(curr_mark, i);
	}
	quick_sort(quantity_st, arr);
	std::cout << arr[0].id << ' ' << arr[quantity_st / 2].id << ' ' << arr[quantity_st - 1].id;
	in.close();
	delete[] arr;
	return 0;
}
