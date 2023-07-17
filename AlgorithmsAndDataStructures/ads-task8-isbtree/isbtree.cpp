#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

template <typename T>
class Queue {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& value) : data(value), next(nullptr) {}
		Node() {}
	};

	Node* head;
	Node* tail;
	int count;

public:
	Queue() : head(nullptr), tail(nullptr), count(0) {}

	~Queue() {
		while (head != nullptr) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void push(const T& value) {
		Node* newNode = new Node(value);
		if (tail == nullptr) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}

	void pop() {
		if (head == nullptr) {
			return;
		}
		Node* temp = head;
		head = head->next;
		delete temp;
		if (head == nullptr) {
			tail = nullptr;
		}
		count--;
	}

	T& front() {
		return head->data;
	}

	bool empty() const {
		return head == nullptr;
	}

	int Size() const {
		return count;
	}
};

class AA_Tree_Set {
	class Node {
	public:
		long data;
		Node* left;
		Node* right;
		int level;
		Node() {
			left = nullptr;
			right = nullptr;
		}
		Node(long val) {
			data = val;
			left = nullptr;
			right = nullptr;
			level = 1;
		}
		~Node() {

		}
	};
	Node* head;
	int length;
public:
	int GetHeadLevel() {
		if (length == 0) {
			return 0;
		}
		return head->level;
	}
	Node* insert(long insert_el, Node* curr = nullptr) {
		if (head == NULL) {
			Node* el = new Node(insert_el);
			head = el;
			++length;
			return head;
		}
		if (curr == NULL) {
			curr = head;
		}
		if ((curr->left == nullptr) && (curr->right == nullptr)) {
			Node* el = new Node(insert_el);
			if (curr->data >= insert_el) {
				curr->left = el;
			}
			else {
				curr->right = el;
			}
			++length;
		}
		else {
			if (curr->data > insert_el) {
				if (curr->left == nullptr) {
					Node* el = new Node(insert_el);
					curr->left = el;
					++length;
				}
				else {
					curr->left = insert(insert_el, curr->left);
				}
			}
			else {
				if (curr->right == nullptr) {
					Node* el = new Node(insert_el);
					curr->right = el;
					++length;
				}
				else {
					curr->right = insert(insert_el, curr->right);
				}
			}
		}
		curr = skew(curr);
		curr = split(curr);
		head = curr;
		return curr;
	}
	static Node* skew(Node* curr) {
		if (curr != nullptr && curr->left != nullptr && curr->left->level == curr->level) {
			Node* L = curr->left;
			curr->left = L->right;
			L->right = curr;
			return L;
		}
		return curr;
	}
	static Node* split(Node* curr) {
		if (curr != nullptr && curr->right != nullptr && curr->right->right != nullptr && curr->right->right->level == curr->level) {
			Node* R = curr->right;
			curr->right = R->left;
			R->left = curr;
			++R->level;
			return R;
		}
		return curr;
	}
	static void definitionLevel(Node* curr) {
		int lev;
		int left_val;
		int right_val;
		if (curr->left == nullptr) {
			left_val = 0;
		}
		else {
			left_val = curr->left->level;
		}
		if (curr->right == nullptr) {
			right_val = 0;
		}
		else {
			right_val = curr->right->level;
		}
		lev = std::min(right_val, left_val) + 1;
		if (lev < curr->level) {
			curr->level = lev;
			if ((curr->right != nullptr) && (lev < curr->right->level)) {
				curr->right->level = lev;
			}
		}

	}
	static Node* rightest_of_left(Node* root) {
		root = root->left;
		while (root->right != nullptr) {
			root = root->right;
		}
		return root;
	}
	static Node* leftest_of_right(Node* root) {
		root = root->right;
		while (root->left != nullptr) {
			root = root->left;
		}
		return root;
	}
	Node* delete_el(long val, Node* curr = nullptr) {
		if (curr == nullptr) {
			--length;
			curr = head;
		}
		if (val > curr->data) {
			curr->right = delete_el(val, curr->right);
		}
		else if (val < curr->data) {
			curr->left = delete_el(val, curr->left);
		}
		else {
			if ((curr->right == nullptr) && (curr->left == nullptr)) {
				if (length == 0) {
					delete head;
					head = nullptr;
				}
				else {
					delete curr;
				}
				return nullptr;
			}
			if (curr->right == nullptr) {
				long del = rightest_of_left(curr)->data;
				curr->left = delete_el(del, curr->left);
				curr->data = del;
			}
			else {
				long del = leftest_of_right(curr)->data;
				curr->right = delete_el(del, curr->right);
				curr->data = del;
			}
		}
		definitionLevel(curr);
		curr = skew(curr);
		curr->right = skew(curr->right);

		if (curr->right != nullptr) {
			curr->right->right = skew(curr->right->right);
		}
		curr = split(curr);
		curr->right = split(curr->right);
		head = curr;
		return curr;
	}
	bool find(long val) {
		Node* curr = head;
		while ((curr != nullptr) && ((curr->left != nullptr) || (curr->right != nullptr))) {
			if (curr->data > val) {
				curr = curr->left;
			}
			else if (curr->data < val) {
				curr = curr->right;
			}
			else {
				return true;
			}
		}
		return ((curr != nullptr) && (curr->data == val));
		return false;
	}
	AA_Tree_Set() {
		length = 0;
		head = nullptr;
	}
	void FreeTree(Node* tree) {
		if (tree->left != nullptr) {
			FreeTree(tree->left);
		}
		if (tree->right != nullptr) {
			FreeTree(tree->right);
		}
		delete tree;
	}
	~AA_Tree_Set() {
		if (head != nullptr) {
			FreeTree(head);
		}
	}
};

class Node {
public:
	bool leaf;
	int quantity_key;
	int* keys;
	int* ptrs;
	Node(bool leaf_, int quantity_key_, int* keys_, int* ptrs_) : leaf(leaf_), quantity_key(quantity_key_), keys(keys_), ptrs(ptrs_) {}
	Node(bool leaf_, int quantity_key_, int* keys_) : leaf(leaf_), quantity_key(quantity_key_), keys(keys_) {}
	Node() {};
	~Node() {};
};

class TreeMap {
private:
	struct TreeNode {
		int key;
		Node value;
		int level;
		TreeNode* left;
		TreeNode* right;

		TreeNode(int key, Node& value) {
			this->key = key;
			this->value = value;
			this->level = 1;
			this->left = nullptr;
			this->right = nullptr;
		}

		~TreeNode() {
			delete left;
			delete right;
		}
	};

	TreeNode* head;
	int length;

	static TreeNode* skew(TreeNode* node) {
		if (node == nullptr || node->left == nullptr || node->left->level != node->level) {
			return node;
		}
		TreeNode* left = node->left;
		node->left = left->right;
		left->right = node;
		return left;
	}

	static TreeNode* split(TreeNode* node) {
		if (node == nullptr || node->right == nullptr || node->right->right == nullptr || node->level != node->right->right->level) {
			return node;
		}
		TreeNode* right = node->right;
		node->right = right->left;
		right->left = node;
		right->level++;
		return right;
	}

	TreeNode* insert(TreeNode* node, int key, Node& value) {
		if (node == nullptr) {
			length++;
			return new TreeNode(key, value);
		}
		if (key < node->key) {
			node->left = insert(node->left, key, value);
		}
		else if (key > node->key) {
			node->right = insert(node->right, key, value);
		}
		else {
			node->value = value;
		}
		node = skew(node);
		node = split(node);
		return node;
	}

	TreeNode* remove(TreeNode* node, int key) {
		if (node == nullptr) {
			return nullptr;
		}
		if (key < node->key) {
			node->left = remove(node->left, key);
		}
		else if (key > node->key) {
			node->right = remove(node->right, key);
		}
		else {
			if (node->left == nullptr && node->right == nullptr) {
				delete node;
				length--;
				return nullptr;
			}
			if (node->left == nullptr) {
				TreeNode* right = node->right;
				node->key = right->key;
				node->value = right->value;
				node->left = right->left;
				node->right = right->right;
				right->left = nullptr;
				right->right = nullptr;
				delete right;
				length--;
			}
			else {
				TreeNode* max = node->left;
				while (max->right != nullptr) {
					max = max->right;
				}
				node->key = max->key;
				node->value = max->value;
				node->left = remove(node->left, max->key);
			}
		}
		node = skew(node);
		node->right = skew(node->right);
		if (node->right != nullptr) {
			node->right->right = skew(node->right->right);
		}
		node = split(node);
		node->right = split(node->right);
		return node;
	}

	TreeNode* find(TreeNode* node, int key) {
		if (node == nullptr) {
			return nullptr;
		}
		if (key < node->key) {
			return find(node->left, key);
		}
		if (key > node->key) {
			return find(node->right, key);
		}
		return node;
	}

public:
	TreeMap() {
		length = 0;
		head = nullptr;
	}

	~TreeMap() {
		delete head;
	}

	void put(int key, Node value) {
		head = insert(head, key, value);
	}

	void remove(int key) {
		head = remove(head, key);
	}

	Node get(int key) {
		TreeNode* node = find(head, key);
		if (node == nullptr) {
			return Node(true, -1, nullptr, nullptr);
		}
		return node->value;
	}

	bool contains(int key) {
		return find(head, key) != nullptr;
	}

	int size() const {
		return length;
	}
};


bool search(const Node& root, int key, TreeMap* indexes_node) {
	int i = 0;
	while (root.keys != nullptr &&  i < root.quantity_key && key > root.keys[i]) {
		i++;
	}
	if (root.keys != nullptr && i != root.quantity_key && root.keys[i] == key) {
		return true;
	}
	if (root.leaf) {
		return false;
	}
	return search(indexes_node->get(root.ptrs[i]), key, indexes_node);
}
int search_past(Node root, TreeMap* indexes_node) {
	if (root.leaf && root.keys != nullptr) {
		return root.keys[0];
	}
	if (root.ptrs != nullptr) {
		root = indexes_node->get(root.ptrs[0]);
	}
	while (!root.leaf) {
		root = indexes_node->get(root.ptrs[root.quantity_key]);
	}
	if (root.keys != nullptr) {
		return root.keys[root.quantity_key - 1];
	}
	return 0;
}
int search_next(Node root, TreeMap* indexes_node) {
	if (root.leaf && root.keys!= nullptr) {
		return root.keys[0];
	}
	if (root.ptrs != nullptr) {
		root = indexes_node->get(root.ptrs[root.quantity_key]);
	}
	while (!root.leaf) {
		root = indexes_node->get(root.ptrs[0]);
	}
	if (root.keys != nullptr) {
		return root.keys[0];
	}
	return 0;
}

int char_to_int(char* str, bool skip_end) {
	int key = 0;
	int mnogitel = 1;
	unsigned long length = strlen(str) - 1;
	if (skip_end) {
		--length;
	}
	while (length >= 0) {
		if (str[length] == '-') {
			key *= -1;
			break;
		}
		key += ((int)str[length] - 48) * mnogitel;
		mnogitel *= 10;
		if (length == 0) {
			break;
		}
		--length;
	}
	return key;
}

int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	int quantity_Node;
	int t;
	int main;
	in >> quantity_Node;
	int** clear = new int* [quantity_Node * 2];
	int insert_clear = 0;
	in >> t;
	in >> main;
	AA_Tree_Set is_used;

	TreeMap indexes_node;

	char type[10];
	for (int i = 0; i < quantity_Node; ++i) {
		in >> type;
		in.get();
		in.get();
		in.get();
		int id;
		in >> id;
		in.get();
		in.get();
		char number_key_str[15];
		in >> number_key_str;
		int number_key = char_to_int(number_key_str, true);
		int insert = 0;
		if (((number_key < 2 * t) && (number_key > t - 2)) || (id == main)) {
			int* keys = new int[number_key];
			clear[insert_clear] = keys;
			++insert_clear;
			char tmp[15];
			int past_key = 0;
			int key = INT_MIN;
			for (int i = 0; i < number_key; ++i) {
				past_key = key;
				in >> tmp;
				if (i == number_key - 1) {
					key = char_to_int(tmp, true);
				}
				else {
					key = char_to_int(tmp, false);

				}
				if (key < past_key) {
					std::cout << "no";
					for (int i = 0; i < insert_clear; ++i) {
						delete[] clear[i];
					}
					delete[] clear;
					return 0;
				}
				keys[insert] = key;
				++insert;
			}

			if (strcmp(type, "branch:") == 0) {
				insert = 0;
				in.get();
				in.get();
				in >> tmp;
				int quantity_node = char_to_int(tmp, true);
				if (quantity_node != number_key + 1) {
					std::cout << "no";
					for (int i = 0; i < insert_clear; ++i) {
						delete[] clear[i];
					}
					delete[] clear;
					return 0;
				}
				int* ptrs = new int[number_key + 1];
				clear[insert_clear] = ptrs;
				++insert_clear;
				for (int i = 0; i < quantity_node; ++i) {
					int ptr = 0;
					in >> tmp;
					if (i == quantity_node - 1) {
						ptr = char_to_int(tmp, true);
					}
					else {
						ptr = char_to_int(tmp, false);
					}
					if (!is_used.find(ptr)) {
						is_used.insert(ptr);
						ptrs[insert] = ptr;
						++insert;
					}
					else {
						std::cout << "no";
						for (int i = 0; i < insert_clear; ++i) {
							delete[] clear[i];
						}
						delete[] clear;
						return 0;
					}
				}
				indexes_node.put(id, Node(false, number_key, keys, ptrs));
			}
			else {
				if (in.get() != '\n') {
					std::cout << "no";
					for (int i = 0; i < insert_clear; ++i) {
						delete[] clear[i];
					}
					delete[] clear;
					return 0;
				}
				indexes_node.put(id, Node(true, number_key, keys));
			}
		}
		else {
			std::cout << "no";
			for (int i = 0; i < insert_clear; ++i) {
				delete[] clear[i];
			}
			delete[] clear;
			return 0;
		}
	}

	Node head = indexes_node.get(main);
	Queue<int> indexes_queue;
	indexes_queue.push(main);
	bool leaf = false;

	while (!indexes_queue.empty()) {
		if (leaf) {
			std::cout << "no";
			for (int i = 0; i < insert_clear; ++i) {
				delete[] clear[i];
			}
			delete[] clear;
			return 0;
		}
		int curr_levele_size = indexes_queue.Size();
		for (int i = 0; i < curr_levele_size; ++i) {
			Node curr_el = indexes_node.get(indexes_queue.front());
			indexes_queue.pop();
			if (curr_el.leaf) {
				leaf = true;
			}
			else {
				for (int j = 0; j < curr_el.quantity_key + 1; ++j) {
					int right_border;
					int left_border;
					if (j == 0) {
						right_border = curr_el.keys[0];
						left_border = INT_MIN;
					}
					else if (j == curr_el.quantity_key) {
						right_border = INT_MAX;
						left_border = curr_el.keys[curr_el.quantity_key - 1];
					}
					else {
						left_border = curr_el.keys[j - 1];
						right_border = curr_el.keys[j];
					}
					indexes_queue.push(curr_el.ptrs[j]);
					Node curr_push = indexes_node.get(curr_el.ptrs[j]);
					if (curr_push.quantity_key == -1) {
						std::cout << "no";
						for (int i = 0; i < insert_clear; ++i) {
							delete[] clear[i];
						}
						delete[] clear;
						return 0;
					}
					for (int itr = 0; itr < curr_push.quantity_key; ++itr) {
						if ((curr_push.keys[itr] < left_border) || (right_border < curr_push.keys[itr])) {
							std::cout << "no";
							for (int i = 0; i < insert_clear; ++i) {
								delete[] clear[i];
							}
							delete[] clear;
							return 0;
						}

					}
				}
			}
		}
	}

	int past_head = search_past(head, &indexes_node);
	int next_head = search_next(head, &indexes_node);

	if ((!search(head, past_head, &indexes_node)) || (!search(head, next_head, &indexes_node))) {
		std::cout << "no";
		for (int i = 0; i < insert_clear; ++i) {
			delete[] clear[i];
		}
		delete[] clear;
		return 0;
	}

	std::cout << "yes";
	in.close();

	for (int i = 0; i < insert_clear; ++i) {
		delete[] clear[i];
	}
	delete[] clear;
	return 0;
}
