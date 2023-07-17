#pragma once
#include<iostream>
#include<fstream>
struct Action {
	bool finalCondition_; //евляется ли финальным состоянием
	bool change_; // изменение на ленте
	int move_; // передвижение по ленте
	int nextCondition_;
	Action() {
		finalCondition_ = 1;
	}
};
struct Condition {
	int numberOfCondition_;
	Action one_; // действие если на ленте еденица
	Action zero_; // действие если на ленте ноль
};

class TuringMachine {
	Condition* conditions_; // массив с программой машины тьюринга
	int lenghtTape_; // длина ленты
	bool* tape_; // лента
	unsigned long long numberOfTakt_; // максимальное количество тактов
	int quantityOfCondition_; // количество состояний
	char** plentyOfCondition_; // массив с названиями состояний
	int outPosition_; // позиция с которой нужно выводить
	bool error_; // проверка на ошибку
	bool aplicate_; // проверка на количество тактов
public:
	// функция для ориентирования по массиву состояний
	int table(char* str, char** array, int lenArray);
	// функция для ориентирования по массиву состояний
	int table(const std::string& str, char** array, int lenArray);
	//конструктор с входнимы файлами
	TuringMachine(const char* inputFile, const char* conditionFile);
	// копирующий конструктор
	TuringMachine(const TuringMachine& machine);
	TuringMachine& operator=(const TuringMachine& right);
	std::string calc(std::string const& init, int maxsteps);
	~TuringMachine();
	const char* getFirstCondition();
	int getNumberOfTakt();
	int getLengthTape();
	int getOutPosition();
	bool getAplicate();
	bool getError();
};
