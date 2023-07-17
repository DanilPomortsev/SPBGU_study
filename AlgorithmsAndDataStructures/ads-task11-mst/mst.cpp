#include <iostream>
#include <fstream>

class DisjoinSets {
public:
    int quantity_el;
    int* parent;
    int* rank;
    DisjoinSets(int quantity_el_) : quantity_el(quantity_el_) {
        parent = new int[quantity_el];
        rank = new int[quantity_el];
        for (int i = 0; i < quantity_el; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~DisjoinSets() {
        delete[] parent;
        delete[] rank;
    }

    int find_set(int el) {
        if (parent[el] == el) {
            return el;
        }
		parent[el] = find_set(parent[el]);
		return parent[el];
    }

    void union_set(int first, int second) {
        int first_set = find_set(first);
        int second_set = find_set(second);
        if (first_set != second_set) {
            if (rank[first_set] > rank[second_set]) {
                parent[second_set] = first;
                if (rank[first] == rank[second]) {
                    ++rank[first];
                }
            }
            else {
                parent[first_set] = second;
                if (rank[first] == rank[second]) {
                    ++rank[second];
                }
            };
        }
    }
};

class Edge {
public:
    int start;
    int end;
    int weight;

    Edge(){}

    Edge(int start_, int end_, int weight_): start(start_), end(end_), weight(weight_){}

    ~Edge(){}

	friend bool operator <(Edge const& c1, Edge const& c2) {
		return c1.weight < c2.weight;
	}
	friend bool operator >(Edge const& c1, Edge const& c2) {
		return c1.weight > c2.weight;
	}
	friend bool operator == (Edge const& c1, Edge const& c2) {
		return c1.weight == c2.weight;
	}
};

std::ostream& operator << (std::ostream& os, const Edge& edge){
	return os << edge.start << " " << edge.end << " " << edge.weight;
}

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

class Para {
public:
	int start;
	int end;
	~Para() {};
	Para(int start_, int end_) : start(start_), end(end_) {}
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

template<typename T>
void quick_sort(int len, T* arr) {
	Stack<Para> stk;
	stk.push(Para(0, len - 1));
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


int main(int argc, char* argv[]){
    std::ifstream in(argv[1]);
    int quantity_top;
    int quantity_edge;
    in >> quantity_top;
    in >> quantity_edge;

    int curr_first_top;
    int curr_second_top;
    int edge_weight;

    Edge* edges = new Edge[quantity_edge];
    for (int i = 0; i < quantity_edge; ++i) {
        in >> curr_first_top;
        in >> curr_second_top;
        in >> edge_weight;
        edges[i] = Edge(curr_first_top, curr_second_top, edge_weight);
    }

	quick_sort(quantity_edge, edges);

	DisjoinSets sets = DisjoinSets(quantity_top);

	int result = 0;

	for (int i = 0; i < quantity_edge; ++i) {
		if (sets.find_set(edges[i].start) != sets.find_set(edges[i].end)) {
			result += edges[i].weight;
			sets.union_set(edges[i].start, edges[i].end);
		}
	}

	std::cout << result;
    in.close();
delete[] edges;
    return 0;
}
