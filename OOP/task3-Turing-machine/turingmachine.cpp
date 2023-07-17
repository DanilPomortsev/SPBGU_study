#include"turingmachine.h"
#include<cstring>
int TuringMachine::table(char* str, char** array, int lenArray) { // функция сопоставляющая состоянию её номер в масииве состояний
	if (lenArray == 0)
		return 0;
	for (int i = 0; i < lenArray; ++i) {
		bool flag_equal = 1;
		for (int j = 0; j < strlen(str); ++j) {
			if (array[i][j] != str[j])
				flag_equal = 0;
		}
		if (flag_equal)
			return i + 1;
	}
	return 0;
}// 
int TuringMachine::table(const std::string& str, char** array, int lenArray) { //функция сопоставляющая состоянию её номер в масииве состояний
	if (lenArray == 0)
		return 0;
	for (int i = 0; i < lenArray; ++i) {
		bool flagEqual = 1;
		for (int j = 0; j < str.length(); ++j) {
			if (array[i][j] != str[j])
				flagEqual = 0;
		}
		if (flagEqual)
			return i + 1;
	}
	return 0;
}
TuringMachine::TuringMachine(const char* conditionFile, const char* inputFile) {
	// считываем ленту и количество тактов
	std::ifstream infile(inputFile);
	if (!infile.is_open()) {
		std::cout << "Problems with file, try one more time";
		throw std::invalid_argument("");
	}
	error_ = 0;
	infile >> lenghtTape_;
	infile >> numberOfTakt_;
	char tapeMalChar[100];
	infile >> tapeMalChar;
	bool* tapeMalBool = new bool[strlen(tapeMalChar)];
	for (int i = 0; i < strlen(tapeMalChar); ++i)
		tapeMalBool[i] = (int)tapeMalChar[i] - 48;
	tape_ = new bool[lenghtTape_];
	int i = 0;
	for (; i < strlen(tapeMalChar); ++i)
		tape_[i] = tapeMalBool[i % strlen(tapeMalChar)];
	for (; i < lenghtTape_; ++i)
		tape_[i] = 0;
	infile.close();
	delete[] tapeMalBool;

	// определяпем количество состояний в файле
	std::ifstream infile2(conditionFile);
	if (!infile2.is_open()) {
		std::cout << "Problems with file, try one more time";
		throw std::invalid_argument("");
	}
	plentyOfCondition_ = new char* [20];
	for (int i = 0; i < 20; ++i)
		plentyOfCondition_[i] = new char[10];
	int indexconditions_ = 0;
	char bin1[10];
	char tekSostTranzit[10];
	char nextSostTranzit[10];
	while (!infile2.eof()) {
		infile2 >> tekSostTranzit;
		char* tekSost = tekSostTranzit;
		infile2 >> bin1;
		infile2 >> bin1;
		infile2 >> nextSostTranzit;
		char* nextSost = nextSostTranzit;
		infile2 >> bin1;
		infile2 >> bin1;
		if (table(tekSost, plentyOfCondition_, indexconditions_) == 0) {
			for (int i = 0; i < strlen(nextSost); ++i)
				plentyOfCondition_[indexconditions_][i] = tekSost[i];
			++indexconditions_;
		}
		if (table(nextSost, plentyOfCondition_, indexconditions_) == 0) {
			for (int i = 0; i < strlen(nextSost); ++i)
				plentyOfCondition_[indexconditions_][i] = nextSost[i];
			++indexconditions_;
		}
	}
	quantityOfCondition_ = indexconditions_;
	infile2.close();

	// заносим программу машину тьюринга в класс с проверкой на ошибки
	std::ifstream infile3(conditionFile);
	if (!infile3.is_open()) {
		std::cout << "Problems with file, try one more time";
		throw std::invalid_argument("");
	}
	conditions_ = new Condition[quantityOfCondition_];
	char tekSost[7];
	char tekZnak[3];
	char bin2[10];
	char nextSost[7];
	char nextZnachenie[3];
	char move_[3];
	while (!infile3.eof()) {
		infile3 >> tekSost;
		if (error_ == 0) {
			if (tekSost[0] != 'q')
				error_ = 1;
			for (int i = 1; i < strlen(tekSost); ++i) {
				if ((tekSost[i] > '9') || (tekSost[i] < '0')) {
					error_ = 1;
					break;
				}
			}
		}
		infile3 >> tekZnak;
		if ((tekZnak[0] != '0') && (tekZnak[0] != '1'))
			error_ = 1;
		infile3 >> bin2;
		infile3 >> nextSost;
		if (error_ == 0) {
			if (nextSost[0] != 'q')
				error_ = 1;
			for (int i = 1; i < strlen(nextSost); ++i) {
				if ((nextSost[i] > '9') || (nextSost[i] < '0')) {
					error_ = 1;
					break;
				}
			}
		}
		infile3 >> nextZnachenie;
		if ((nextZnachenie[0] != '0') && (nextZnachenie[0] != '1'))
			error_ = 1;
		infile3 >> move_;
		if ((move_[0] != 'R') && (move_[0] != 'L') && (move_[0] != 'N'))
			error_ = 1;
		int index = table(tekSost, plentyOfCondition_, quantityOfCondition_) - 1;
		conditions_[index].numberOfCondition_ = index;
		if (tekZnak[0] == '1') {
			conditions_[index].one_.finalCondition_ = 0;
			conditions_[index].one_.nextCondition_ = table(nextSost, plentyOfCondition_, quantityOfCondition_) - 1;
			conditions_[index].one_.change_ = (int)nextZnachenie[0] - 48;
			if (move_[0] == 'L')
				conditions_[index].one_.move_ = 1;
			else if (move_[0] == 'R')
				conditions_[index].one_.move_ = 2;
			else if (move_[0] == 'N')
				conditions_[index].one_.move_ = 0;
		}
		else if (tekZnak[0] == '0') {
			conditions_[index].zero_.finalCondition_ = 0;
			conditions_[index].zero_.nextCondition_ = table(nextSost, plentyOfCondition_, quantityOfCondition_) - 1;
			conditions_[index].zero_.change_ = (int)nextZnachenie[0] - 48;
			if (move_[0] == 'L')
				conditions_[index].zero_.move_ = 1;
			else if (move_[0] == 'R')
				conditions_[index].zero_.move_ = 2;
			else if (move_[0] == 'N')
				conditions_[index].zero_.move_ = 0;
		}
	}
	infile3.close();
}
TuringMachine::TuringMachine(const TuringMachine& machine) {
	lenghtTape_ = machine.lenghtTape_;
	tape_ = new bool[lenghtTape_];
	for (int i = 0; i < lenghtTape_; ++i)
		tape_[i] = machine.tape_[i];
	numberOfTakt_ = machine.numberOfTakt_;
	quantityOfCondition_ = machine.quantityOfCondition_;

	plentyOfCondition_ = new char* [quantityOfCondition_];
	for (int i = 0; i < quantityOfCondition_; ++i) {
		plentyOfCondition_[i] = new char[strlen(machine.plentyOfCondition_[i])];
	}
	for (int i = 0; i < quantityOfCondition_; ++i) {
		for (int j = 0; j < strlen(machine.plentyOfCondition_[i]); ++j)
			plentyOfCondition_[i][j] = machine.plentyOfCondition_[i][j];
	}
	conditions_ = new Condition[machine.quantityOfCondition_];
	for (int i = 0; i < quantityOfCondition_; ++i) {
		conditions_[i].numberOfCondition_ = machine.conditions_[i].numberOfCondition_;

		conditions_[i].one_.change_ = machine.conditions_[i].one_.change_;
		conditions_[i].one_.finalCondition_ = machine.conditions_[i].one_.finalCondition_;
		conditions_[i].one_.move_ = machine.conditions_[i].one_.move_;
		conditions_[i].one_.nextCondition_ = machine.conditions_[i].one_.nextCondition_;

		conditions_[i].zero_.change_ = machine.conditions_[i].zero_.change_;
		conditions_[i].zero_.finalCondition_ = machine.conditions_[i].zero_.finalCondition_;
		conditions_[i].zero_.move_ = machine.conditions_[i].zero_.move_;
		conditions_[i].zero_.nextCondition_ = machine.conditions_[i].zero_.nextCondition_;
	}
	error_ = machine.error_;
	aplicate_ = machine.aplicate_;
}
TuringMachine& TuringMachine::operator=(const TuringMachine& right) {
	if (conditions_ != nullptr)
		delete[] conditions_;
	if (tape_ != nullptr)
		delete[] tape_;
	for (int i = 0; i < quantityOfCondition_; ++i)
		if (plentyOfCondition_[i] != nullptr)
			delete[] plentyOfCondition_[i];
	if (plentyOfCondition_ != nullptr)
		delete[] plentyOfCondition_;

	lenghtTape_ = right.lenghtTape_;
	bool* tape_ = new bool[lenghtTape_];
	for (int i = 0; i < lenghtTape_; ++i)
		tape_[i] = right.tape_[i];
	numberOfTakt_ = right.numberOfTakt_;
	quantityOfCondition_ = right.quantityOfCondition_;

	plentyOfCondition_ = new char* [quantityOfCondition_];
	for (int i = 0; i < quantityOfCondition_; ++i)
		plentyOfCondition_[i] = new char[strlen(right.plentyOfCondition_[i])];

	for (int i = 0; i < quantityOfCondition_; ++i) {
		for (int j = 0; j < strlen(plentyOfCondition_[i]); ++j)
			plentyOfCondition_[i][j] = right.plentyOfCondition_[i][j];
	}

	conditions_ = new Condition[quantityOfCondition_];
	for (int i = 0; i < quantityOfCondition_; ++i) {
		conditions_[i].numberOfCondition_ = right.conditions_[i].numberOfCondition_;

		conditions_[i].one_.change_ = right.conditions_[i].one_.change_;
		conditions_[i].one_.finalCondition_ = right.conditions_[i].one_.finalCondition_;
		conditions_[i].one_.move_ = right.conditions_[i].one_.move_;
		conditions_[i].one_.nextCondition_ = right.conditions_[i].one_.move_;


		conditions_[i].zero_.change_ = right.conditions_[i].zero_.change_;
		conditions_[i].zero_.finalCondition_ = right.conditions_[i].zero_.finalCondition_;
		conditions_[i].zero_.move_ = right.conditions_[i].zero_.move_;
		conditions_[i].zero_.nextCondition_ = right.conditions_[i].zero_.move_;
	}
	return *this;
}
std::string TuringMachine::calc(std::string const& init, int maxsteps) {
	int tekSost = table(init, plentyOfCondition_, quantityOfCondition_) - 1;
	int tekPos = 0;
	int quantityOfTakt = 0;// определяем начальное состояние
	while (true) {
		if (quantityOfTakt + 1 >= maxsteps) { // проверка на количество тактов
			aplicate_ = 1;
			break;
		}
		if (tape_[tekPos] == 0) { // если на ленте ноль
			if (conditions_[tekSost].zero_.finalCondition_) {
				outPosition_ = tekPos;// записываем позицию вывода
				break;
			}
			tape_[tekPos] = conditions_[tekSost].zero_.change_; // меняем ечейку в ленте
			//передвигаемся
			if (conditions_[tekSost].zero_.move_ == 2) {
				if (tekPos == lenghtTape_ - 1)
					tekPos = 0;
				else
					++tekPos;
			}
			if (conditions_[tekSost].zero_.move_ == 1) {
				if (tekPos == 0)
					tekPos = lenghtTape_ - 1;
				else
					--tekPos;
			}
			tekSost = conditions_[tekSost].zero_.nextCondition_;
			++quantityOfTakt;
		}
		else if (tape_[tekPos] == 1) { // если на ленте еденица
			if (conditions_[tekSost].one_.finalCondition_) {
				outPosition_ = tekPos;// записываем позицию вывода
				break;
			}
			tape_[tekPos] = conditions_[tekSost].one_.change_;// меняем ечейку в ленте
			//передвигаемся
			if (conditions_[tekSost].one_.move_ == 2) {
				if (tekPos == lenghtTape_ - 1)
					tekPos = 0;
				else
					++tekPos;
			}
			if (conditions_[tekSost].one_.move_ == 1) {
				if (tekPos == 0)
					tekPos = lenghtTape_ - 1;
				else
					--tekPos;
			}
			tekSost = conditions_[tekSost].one_.nextCondition_;
			++quantityOfTakt;
		}
	}
	int tekPosCopy = tekPos;
	int lastone_;
	while (tekPos != tekPosCopy - 1) {
		if (tape_[tekPos] == 1)
			lastone_ = tekPos;
		if ((tekPosCopy == 0) && (tekPos == lenghtTape_ - 1)) {
			break;
		}
		if (tekPos == lenghtTape_ - 1)
			tekPos = 0;
		else
			++tekPos;
	}
	int resultLen;
	if (lastone_ > tekPosCopy)
		resultLen = lastone_ - tekPosCopy + 1;
	else if (lastone_ == tekPosCopy)
		resultLen = 1;
	else
		resultLen = lenghtTape_ - (tekPosCopy - lastone_) + 1;
	//записываем ленту полностью
	std::string result(resultLen, '0');
	int i = 0;
	while (true) {
		if (i == resultLen)
			break;
		result[i] = (char)(tape_[tekPosCopy] + 48);
		++i;
		if (tekPosCopy == lenghtTape_ - 1)
			tekPosCopy = 0;
		else
			++tekPosCopy;
	}
	return result;
}
TuringMachine:: ~TuringMachine() {
	if (conditions_ != nullptr)
		delete[] conditions_;
	if (tape_ != nullptr)
		delete[] tape_;
	for (int i = 0; i < quantityOfCondition_; ++i)
		if (plentyOfCondition_[i] != nullptr)
			delete[] plentyOfCondition_[i];
	if (plentyOfCondition_ != nullptr)
		delete[] plentyOfCondition_;
}
const char* TuringMachine::getFirstCondition() {
	return this->plentyOfCondition_[0];
}
int TuringMachine::getNumberOfTakt() {
	return this->numberOfTakt_;
}
int TuringMachine::getLengthTape() {
	return lenghtTape_;
}
int TuringMachine::getOutPosition() {
	return outPosition_;
}
bool TuringMachine::getAplicate() {
	return aplicate_;
}
bool TuringMachine::getError() {
	return error_;
}
