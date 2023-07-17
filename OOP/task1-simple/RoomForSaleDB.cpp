#include<iostream>
#include<fstream>
#include<sstream>

int fromStrToInt(const char* str) {
	int result = 0;
	int pow10 = 1;
	for (int i = strlen(str) - 1; i != -1; --i, pow10 *= 10)
		result += (str[i] - 48) * pow10;
	return result;
}
bool dataChek(const char* data) {
	int countOfDouts = 0;
	bool lastIsDouts = 0;
	bool errorDateFormat = 0;
	bool invalidData = 0;
	for (int i = 0; i < strlen(data); ++i) {
		if ((data[i] != '.') && (data[i] < '0') && (data[i] > '9')) {
			std::cout << "Wrong date format: " << data << std::endl;
			return 0;
		}
		else if (data[i] == '.') {
			if (lastIsDouts)
				errorDateFormat = 1;
			++countOfDouts;
			lastIsDouts = 1;
		}
		else
			lastIsDouts = 0;
	}
	if (countOfDouts != 2)
		errorDateFormat = 1;
	if (errorDateFormat) {
		std::cout << "Wrong date format: " << data << std::endl;
		return 0;
	}
	int j = 0;
	int firstLen = 0;
	int secondLen = 0;
	int thirdLen = 0;
	int tekSost = 1;
	while (j != strlen(data)) {
		if (data[j] == '.') {
			++j;
			++tekSost;
			continue;
		}
		if (tekSost == 1)
			++firstLen;
		else if (tekSost == 2)
			++secondLen;
		else if (tekSost == 3)
			++thirdLen;
		++j;
	}
	if (firstLen != 2) {
		invalidData = 1;
		std::cout << "Day value is invalid:" << std::endl;
		for (int i = 0; i < firstLen; ++i)
			std::cout << data[i];
		std::cout << std::endl;
	}
	if (secondLen != 2) {
		invalidData = 1;
		std::cout << "Month value is invalid:" << std::endl;
		for (int i = firstLen + 1; i < firstLen + 1 + secondLen; ++i)
			std::cout << data[i];
		std::cout << std::endl;
	}
	if (invalidData)
		return 0;
	char first[3] = "00";
	char second[3] = "00";
	first[0] = data[0];
	first[1] = data[1];
	int firstInt = fromStrToInt(first);
	second[0] = data[3];
	second[1] = data[4];
	int secondInt = fromStrToInt(second);
	if ((firstInt > 31) || (firstInt < 1)) {
		invalidData = 1;
		std::cout << "Day value is invalid:";
		for (int i = 0; i < firstLen; ++i)
			std::cout << data[i];
		std::cout << std::endl;
	}
	if ((secondInt > 12) || (secondInt < 1)) {
		invalidData = 1;
		std::cout << "Month value is invalid:";
		for (int i = 0; i < firstLen; ++i)
			std::cout << data[i];
		std::cout << std::endl;
	}
	if (invalidData)
		return 0;
	return 1;
}
void options() {
	std::cout << "load имя_файла_с_БД — чтение базы данных из файла" << std::endl;
	std::cout << "save имя_файла_с_БД — запись базы данных в файл" << std::endl;
	std::cout << "add дата объявления, количество комнат, этаж, площадь, адрес, цена — добавление в картотеку данных о квартирах (добавление записи)" << std::endl;
	std::cout << "del id_ — удаление записи по её уникальному номеру id_" << std::endl;
	std::cout << "print — вывод всего списка квартир, отсортированных по цене" << std::endl;
	std::cout << "print N — вывод списка квартир с заданным количеством комнат N, отсортированных по цене" << std::endl;
	std::cout << "export имя_файла — вывод всего списка квартир в текстовый файл" << std::endl;
	std::cout << "find id_ — поиск в картотеке подходящего варианта обмена для записи с номером id_: при равенстве количества комнат и этажа и различии площадей в пределах 20% квартира считается подходящей," << std::endl;
	std::cout << "еxit - завершение работы с программой" << std::endl << std::endl;

}

struct Flat {
	int id_;
	char date_[11];
	int number_OfRooms_;
	int floor_;
	int square_;
	char address_[64];
	int price_;
	Flat(char* date, char* price, char* number_OfRooms, char* floor, char* square, char* address);
	Flat(const Flat& tmp);
	Flat& operator=(const Flat& tmp);
	Flat();
	friend std::ostream& operator<< (std::ostream& out, Flat& tmp);
};

struct DataBase {
	int iid_ = 1;
	int number_;
	Flat* data_;
	DataBase(const char* name);
	DataBase(int number, Flat* data);
	void sort();
	void print();
	void printN(int N);
	void addFlat(Flat& Flat_);
	void save(const char* name);
	void exportt(const char* name);
	void del(int index);
	void findid_(int index);
	~DataBase();
};

int main() {
	setlocale(LC_ALL, "Russian");
	DataBase db(0, nullptr);
	while (true) {
		options();
		char input[256];
		std::cin.getline(input, 256);
		int counterOfWords = 0;
		for (int i = 0; i < strlen(input); ++i) {
			if (input[i] == ' ')
				++counterOfWords;
		}
		++counterOfWords;
		if (counterOfWords == 1) {
			if (((strcmp(input, "add") == 0) || (strcmp(input, "find") == 0) 
				|| (strcmp(input, "export") == 0) || (strcmp(input, "print") == 0) 
				|| (strcmp(input, "del") == 0) || (strcmp(input, "load") == 0) 
				|| (strcmp(input, "save") == 0) || (strcmp(input, "exit") == 0)) == 0) {
				std::cout << "Unknown command:" << input << std::endl;
				continue;
			}
			else if (strcmp(input, "print") == 0)
				db.print();
			else if (strcmp(input, "exit") == 0)
				break;

		}
		else if (counterOfWords == 2) {
			std::istringstream iinput(input);
			char words[2][64];
			int i = 0;
			while (!iinput.eof()) {
				iinput >> words[i];
				++i;
			}
			if (((strcmp(words[0], "add") == 0) || (strcmp(words[0], "find") == 0) 
				|| (strcmp(words[0], "export") == 0) || (strcmp(words[0], "print") == 0) 
				|| (strcmp(words[0], "del") == 0) || (strcmp(words[0], "load") == 0) 
				|| (strcmp(input, "save") == 0) || (strcmp(input, "exit") == 0)) == 0) {
				std::cout << "Unknown command:" << words[0] << std::endl;
				continue;
			}
			else if (strcmp(words[0], "load") == 0) {
				db = DataBase(words[1]);
			}
			else if (strcmp(words[0], "save") == 0) {
				db.save(words[1]);
			}
			else if (strcmp(words[0], "del") == 0) {
				int index = fromStrToInt(words[1]);
				db.del(index);
			}
			else if (strcmp(words[0], "print") == 0) {
				int index = fromStrToInt(words[1]);
				db.printN(index);
			}
			else if (strcmp(words[0], "export") == 0) {
				db.exportt(words[1]);
			}
			else if (strcmp(words[0], "find") == 0) {
				int index = fromStrToInt(words[1]);
				db.findid_(index);
			}
		}
		else if (counterOfWords == 7) {
			std::istringstream iinput(input);
			char words[7][64];
			int i = 0;
			while (!iinput.eof()) {
				iinput >> words[i];
				++i;
			}
			if (((strcmp(words[0], "add") == 0) || (strcmp(words[0], "find") == 0) 
				|| (strcmp(words[0], "export") == 0) || (strcmp(words[0], "print") == 0) 
				|| (strcmp(words[0], "del") == 0) || (strcmp(words[0], "load") == 0) 
				|| (strcmp(input, "save") == 0) || (strcmp(input, "exit") == 0)) == 0) {
				std::cout << "Unknown command:" << words[0] << std::endl;
				continue;
			}
			else if (strcmp(words[0], "add") == 0) {
				Flat nnew(words[1], words[2], words[3], words[4], words[5], words[6]);
				db.addFlat(nnew);
				continue;
			}
		}
		else
			std::cout << "Please, read instruction one more time and try to enter comman again" << std::endl;
	}
	return 0;
}

Flat::Flat(char* date, char* price, char* number_OfRooms, char* floor, char* square, char* address) : number_OfRooms_(fromStrToInt(number_OfRooms)), floor_(fromStrToInt(floor)), square_(fromStrToInt(square)), price_(fromStrToInt(price)), id_(1) {
	strcpy_s(date_, 11, date);
	strcpy_s(address_, 64, address);
}
Flat::Flat(const Flat& tmp) :id_(tmp.id_), number_OfRooms_(tmp.number_OfRooms_), floor_(tmp.floor_), square_(tmp.square_), price_(tmp.price_) {
	strcpy_s(date_, 11, tmp.date_);
	strcpy_s(address_, 64, tmp.address_);
}
Flat& Flat::operator=(const Flat& tmp) {
	id_ = tmp.id_;
	strcpy_s(date_, 11, tmp.date_);
	number_OfRooms_ = tmp.number_OfRooms_;
	floor_ = tmp.floor_;
	square_ = tmp.square_;
	strcpy_s(address_, 64, tmp.address_);
	price_ = tmp.price_;
	return *this;
}
Flat::Flat() {}
std::ostream& operator<< (std::ostream& out, Flat& tmp) {
	out << tmp.id_ << ",";
	out << tmp.date_ << ",";
	out << tmp.price_ << ",";
	out << tmp.number_OfRooms_ << ",";
	out << tmp.floor_ << ",";
	out << tmp.square_ << ",";
	out << tmp.address_ << '\n';
	return out;
}

DataBase::DataBase(const char* name) {
	std::ifstream infile1(name);
	if (!infile1.is_open())
		std::cout << "Some problems with file";
	char str[1024];
	int count = 0;
	char datta[64];
	bool isNotRight[1000];
	for (int i = 0; i < 1000; ++i)
		isNotRight[i] = 0;
	int i = 0;
	int rightFlatCount = 0;
	while (!infile1.eof()) {
		infile1 >> datta;
		if (dataChek(datta)) {
			infile1.getline(str, 1024);
			++count;
		}
		else {
			infile1.getline(str, 1024);
			isNotRight[i] = 1;
		}
		++i;
	}
	infile1.close();

	std::ifstream infile2(name);
	if (!infile2.is_open())
		std::cout << "Some problems with file";
	Flat* array = new Flat[count];
	for (int j = 0; j < i; ++j) {
		if (isNotRight[j] == 1)
			continue;
		else {
			infile2 >> array[rightFlatCount].address_;
			infile2 >> array[rightFlatCount].price_;
			infile2 >> array[rightFlatCount].number_OfRooms_;
			infile2 >> array[rightFlatCount].floor_;
			infile2 >> array[rightFlatCount].square_;
			infile2 >> array[rightFlatCount].date_;
			array[rightFlatCount].id_ = iid_;
			++iid_;
			++rightFlatCount;
		}
	}
	number_ = count;
	data_ = array;
	infile2.close();
}
DataBase::DataBase(int number, Flat* data) : number_(number), data_(data) {}
void DataBase::sort() {
	for (int i = 0; i < number_ - 1; ++i) {
		int max = i;
		for (int j = i + 1; j < number_; ++j) {
			if (data_[max].price_ < data_[j].price_)
				max = j;
		}
		Flat tmp;
		tmp = data_[max];
		data_[max] = data_[i];
		data_[i] = tmp;
	}
}
void DataBase::print() {
	this->sort();
	for (int i = 0; i < number_; ++i)
		std::cout << data_[i];
}
void DataBase::printN(int N) {
	this->sort();
	for (int i = 0; i < number_; ++i) {
		if (data_[i].number_OfRooms_ == N)
			std::cout << data_[i];
	}
}
void DataBase::addFlat(Flat& Flat_) {
	Flat* tmp = new Flat[number_ + 1];
	for (int i = 0; i < number_; ++i) {
		tmp[i].id_ = this->data_[i].id_;
		strcpy_s(tmp[i].date_, 11, this->data_[i].date_);
		tmp[i].number_OfRooms_ = this->data_[i].number_OfRooms_;
		tmp[i].floor_ = this->data_[i].floor_;
		tmp[i].square_ = this->data_[i].square_;
		strcpy_s(tmp[i].address_, 64, this->data_[i].address_);
		tmp[i].price_ = this->data_[i].price_;
	}
	if (data_ != nullptr)
		delete[] data_;
	tmp[number_] = Flat_;
	data_ = tmp;
	data_[number_].id_ = iid_;
	++iid_;
	++number_;
}
void DataBase::save(const char* name) {
	std::ofstream outfile(name);
	if (!outfile.is_open()) {
		std::cout << "some problems";
		return;
	}
	for (int i = 0; i < number_; ++i)
		outfile << data_[i];
	outfile.close();
}
void DataBase::exportt(const char* name) {
	std::ofstream outfile(name, std::ios_base::binary);
	if (!outfile.is_open()) {
		std::cout << "problems with file";
		return;
	}
	for (int i = 0; i < number_; ++i) {
		outfile << data_[i].address_ << ' ';
		outfile << (char)((data_[i].date_[0] - 48) * 10 + data_[i].date_[1] - 48) << ' ';
		outfile << (char)((data_[i].date_[3] - 48) * 10 + data_[i].date_[4] - 48) << ' ';
		int year = (data_[i].date_[6] - 48) * 1000 + (data_[i].date_[7] - 48) * 100 + (data_[i].date_[8] - 48) * 10 + data_[i].date_[9] - 48;
		outfile << (char)(year / 256) << (char)(year % 256) << ' ';
		outfile << (char)data_[i].floor_ << ' ';
		outfile << (char)data_[i].number_OfRooms_ << ' ';

		//сначала передаём в скольки байтах будет передвно id_, затем с помощью символов работаем с байтами и передаём нкжное число, с последующими параметрами точно так же
		int idCopy = data_[i].id_;
		int charLenId = 0;
		while (idCopy) {
			++charLenId;
			idCopy /= 256;
		}
		idCopy = data_[i].id_;
		char* idChar = new char[charLenId];
		for (int i = charLenId - 1; i > 0; --i) {
			idChar[i] = idCopy % 256;
			idCopy /= 256;
		}
		for (int i = 0; i < charLenId; ++i)
			outfile << idChar[i];

		int priceCopy = data_[i].price_;
		int charLenPrice = 0;
		while (priceCopy) {
			++charLenPrice;
			priceCopy /= 256;
		}
		priceCopy = data_[i].price_;
		char* priceChar = new char[charLenPrice];
		for (int i = charLenPrice - 1; i > 0; --i) {
			priceChar[i] = priceCopy % 256;
			priceCopy /= 256;
		}
		for (int i = 0; i < charLenPrice; ++i)
			outfile << priceChar[i];

		int squareCopy = data_[i].square_;
		int charLenSquare = 0;
		while (squareCopy) {
			++charLenSquare;
			squareCopy /= 256;
		}
		squareCopy = data_[i].square_;
		char* squareChar = new char[charLenSquare];
		for (int i = charLenSquare - 1; i > 0; --i) {
			squareChar[i] = squareCopy % 256;
			squareCopy /= 256;
		}
		for (int i = 0; i < charLenSquare; ++i)
			outfile << priceChar[i];

		outfile << std::endl;
	}
	outfile.close();
}
void DataBase::del(int index) {
	int i = 0;
	for (; data_[i].id_ != index; ++i) {
		if (i == number_) {
			std::cout << "No such id_" << std::endl;
			return;
		}
	}
	for (; i < number_ - 1; ++i)
		data_[i] = data_[i + 1];
	--number_;
	for (int i = 0; i < number_; ++i)
		std::cout << data_[i];
}
void DataBase::findid_(int index) {
	int i = 0;
	for (; i < number_; ++i) {
		if (data_[i].id_ == index)
			break;
	}
	for (int j = 0; j < number_; ++j) {
		if (i == j)
			continue;
		if ((data_[i].floor_ == data_[j].floor_) && (data_[i].number_OfRooms_ == data_[j].number_OfRooms_)
			&& ((data_[j].square_ > data_[i].square_ * 0.8) || (data_[i].square_ * 1.2 > data_[j].square_)))
			std::cout << data_[j];
	}
}
DataBase::~DataBase() {
	if (data_ != nullptr)
		delete[] data_;
}
