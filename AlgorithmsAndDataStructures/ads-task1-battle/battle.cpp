#include <iostream>
#include <fstream>

class Card {
public:
	int value;
	Card() {}
	Card(char ch) {
		if (ch == '2') {
			value = 1;
		}
		else if (ch == '3') {
			value = 2;
		}
		else if (ch == '4') {
			value = 3;
		}
		else if (ch == '5') {
			value = 4;
		}
		else if (ch == '6') {
			value = 5;
		}
		else if (ch == '7') {
			value = 6;
		}
		else if (ch == '8') {
			value = 7;
		}
		else if (ch == '9') {
			value = 8;
		}
		else if (ch == '1') {
			value = 9;
		}
		else if (ch == 'J') {
			value = 10;
		}
		else if (ch == 'Q') {
			value = 11;
		}
		else if (ch == 'K') {
			value = 12;
		}
		else if (ch == 'A') {
			value = 13;
		}
	}
	friend bool operator <(Card c1, Card c2)
	{
		if (c1.value == 1 && c2.value == 13) {
			return false;
		}
		if (c1.value == 13 && c2.value == 1) {
			return true;
		}
		return c1.value < c2.value;
	}
	friend bool operator ==(Card c1, Card c2)
	{
		return c1.value == c2.value;
	}
	friend bool operator >(Card c1, Card c2)
	{
		if (c1.value == 1 && c2.value == 13) {
			return true;
		}
		if (c1.value == 13 && c2.value == 1) {
			return false;
		}
		return c1.value > c2.value;
	}
};

template<typename T>
class Queue_fix {
	int lenght;
	int max_lenght;
	int left;
	int right;
	T* data;
public:
	Queue_fix(int lenght_) {
		lenght = 0;
		right = 0;
		left = 0;
		max_lenght = lenght_;
		data = new T[lenght_];
	}
	~Queue_fix() {
		if (max_lenght > 0) {
			delete[] data;
		}
	}
	void push(T new_element) {
		data[right] = new_element;
		if ((right == max_lenght-1) && (left != 0)) {
			right = 0;
		}
		else {
			++right;
		}
		++lenght;
	}
	int size() { return lenght; }
	T pop() {
		T result = data[left];
		if (left == max_lenght-1) {
			left = 0;
		}
		else {
			++left;
		}
		--lenght;
		return result;
	}
};

int main(int argc, char* argv[]) {
	Queue_fix<Card> first_player(52);
	Queue_fix<Card> second_player(52);
	std::ifstream file;
	file.open(argv[1]);
	for (int i = 0; i < 26; ++i) {
		char ch;
		char bin[10];
		file >> ch;
		file >> bin;
		if (bin[0] == '0') {
			file >> bin;
		}
		first_player.push(Card(ch));
	}
	for (int i = 0; i < 26; ++i) {
		char ch;
		char bin[10];
		file >> ch;
		file >> bin;
		if (bin[0] == '0') {
			file >> bin;
		}
		second_player.push(Card(ch));
	}
	int itr_count = 0;
	Card card_1;
	Card card_2;
	while ((first_player.size() != 52) || (second_player.size() != 52)) { 
		++itr_count;
		if (itr_count > 1000000) {
			std::cout << "unknown";
			break;
		}
		card_1 = first_player.pop();
		card_2 = second_player.pop();
		if (card_1 < card_2) {
			second_player.push(card_1);
			second_player.push(card_2);
		}
		else if (card_1 > card_2) {
			first_player.push(card_1);
			first_player.push(card_2);
		}
		else if (card_1 == card_2) {
			bool flag_draw = false;
			Queue_fix<Card> first_player_hand(52);
			Queue_fix<Card> second_player_hand(52);
			first_player_hand.push(card_1);
			second_player_hand.push(card_2);
			while (card_1 == card_2) {
				card_1 = first_player.pop();
				card_2 = second_player.pop();
				first_player_hand.push(card_1);
				second_player_hand.push(card_2);
				if (first_player.size() == 0 && second_player.size() == 0) {
					std::cout << "draw";
					flag_draw = true;
					break;
				}
			}
			if (flag_draw) {
				break;
			}
			if (card_1 > card_2) {
				while (first_player_hand.size() != 0) {
					first_player.push(first_player_hand.pop());
					first_player.push(second_player_hand.pop());
				}
			}
			else {
				while (first_player_hand.size() != 0) {
					second_player.push(first_player_hand.pop());
					second_player.push(second_player_hand.pop());
				}
			}

		}
		if (first_player.size() == 52) {
			std::cout << "first";
			break;
		}
		if (second_player.size() == 52) {
			std::cout << "second";
			break;
		}
	}
	return 0;
}
