#include <iostream>
#include <fstream>

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


class AA_Tree_Set {
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



int main(int argc, char* argv[]) {
	std::ifstream in(argv[1]);
	std::ofstream out("output.txt");
	int quantity_of_operation;
	in >> quantity_of_operation;
	AA_Tree_Set set = AA_Tree_Set();
	for (int i = 0; i < quantity_of_operation; ++i) {
		char action;
		long number;
		in >> action;
		in >> number;
		if (action == '+') {
			set.insert(number);
			out << set.GetHeadLevel() << std::endl;
		}
		else if (action == '-') {
			set.delete_el(number);
			out << set.GetHeadLevel() << std::endl;
		}
		else if (action == '?') {
			if (set.find(number)) {
				out << "true" << std::endl;
			}
			else {
				out << "false" << std::endl;
			}

		}
	}
	in.close();
	out.close();
	return 0;
}
