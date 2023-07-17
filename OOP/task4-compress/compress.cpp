#include<iostream>
#include<list>
#include<vector>
#include<fstream>
#include<string>
#include<map>

// класс узла для дерева кодов(Хаффман)
class Node
{
public:
	bool codeCompleted_;
	int weight_;
	char simvol_;
	Node* left_, * right_;

	Node() {
		simvol_ = 0;
		codeCompleted_ = 0;
		left_ = nullptr;
		right_ = nullptr;
	}
	~Node() {
		if (left_) delete left_;
		if (right_) delete right_;
		left_ = right_ = nullptr;
	}
};
//функция увеличивающая бинарный код на 1
void incrimentBinnary(std::list<bool>& code) {
	std::list<bool>::iterator itr = code.end();
	--itr;
	if (*itr == 0)
		*itr = 1;
	else {
		while (*itr == 1) {
			*itr = 0;
			if (itr == code.begin())
				code.push_front(0);
			--itr;
		}
		*itr = 1;
	}
}
//функция заполняющая таблицу кодов(Хаффман)
void tableBuild(const Node* three, std::vector<bool>& code2, std::map<char, std::vector<bool>>& table) {
	if (three->left_ != NULL)
	{
		code2.push_back(0);
		tableBuild(three->left_, code2, table);
	}

	if (three->right_ != NULL)
	{
		code2.push_back(1);
		tableBuild(three->right_, code2, table);
	}

	if (three->left_ == NULL && three->right_ == NULL) {
		table[three->simvol_] = code2;
	}
	if (code2.size() != 0)
		code2.pop_back();
}
void huffman(const std::string& in, const std::string& out) {
	std::vector<bool> code2; // бинарный код для заполнения табицы кодов(Хаффман)
	std::map<char, std::vector<bool>> table;// таблица кодов(Хаффман)
	std::ifstream infile(in, std::ios_base::binary);
	if (!infile.is_open()) {
		std::cout << "Some problems";
		return;
	}
	std::ofstream outfile(out, std::ios_base::binary);
	if (!outfile.is_open()) {
		std::cout << "Some problems";
		return;
	}

	//считываем частоту появления каждого символа, считаем количество байт
	int countOfBite = 0;
	std::vector<int> array(256);
	while (!infile.eof()) {
		int simvol = infile.get();
		if (simvol < 0)
			simvol += 256;
		++array[simvol];
		++countOfBite;
	}
	infile.close();

	//создаём узлы для дерева, выводя в сжимаемыый файл частоту каждого символа
	int count = 0;
	for (int i = 0; i < 256; ++i) {
		if (array[i] != 0)
			++count;
	}
	std::list<char> countOfBiteArr; // количество байт в сжимаемом файле
	char len = 0;
	while (countOfBite > 0) {
		countOfBiteArr.push_front(countOfBite % 256);
		countOfBite /= 256;
		++len;
	}
	outfile << '0' << countOfBiteArr.size(); // выводим код сжатия Хаффмана и количество символов в которых передаётся количество байт в сжимаемом файле
	auto itr = countOfBiteArr.begin();
	for (int i = 0; i < len; ++i, ++itr)// выводим количество байт в сжимаемом файле
		outfile << *itr;

	outfile << (char)count;// выводим количество символов с ненулевой встречаемостью
	//создаём узлы дерева
	std::list<Node*> Three;
	for (int i = 0; i < 256; ++i) {
		if (array[i] != 0) {
			Node* element = new Node;
			element->simvol_ = i;
			outfile << element->simvol_; //выводим символ
			int quantityOfBit = 0;
			int arrICopy = array[i];
			for (; arrICopy > 0; arrICopy /= 2)
				++quantityOfBit;
			arrICopy = array[i];
			outfile << (quantityOfBit / 8) + 1; //количество символов в которых передаётся частота появления символа
			std::vector<char> m((quantityOfBit / 8) + 1, 0);
			for (int i = 0; i < (quantityOfBit / 8) + 1; ++i) {
				for (int pow2 = 128; pow2 > 0; pow2 /= 2)
					m[i] += arrICopy & pow2;
				arrICopy /= 256;
			}
			for (int i = 0; i < m.size(); ++i)// выводим частоту появления символа
				outfile << m[m.size() - i - 1];
			element->weight_ = array[i];
			Three.push_back(element);
		}
	}

	//создаём дерево, последовательно соединяя узлы с наименьшим весом
	while (Three.size() != 1) {
		Three.sort([](Node* left_, Node* right_) {return left_->weight_ < right_->weight_; });
		std::list<Node*>::iterator itr = Three.begin();
		Node* Unity = new Node;
		Unity->weight_ = (*itr)->weight_;
		Unity->left_ = *itr;
		++itr;
		Unity->weight_ += (*itr)->weight_;
		Unity->right_ = *itr;
		Three.push_back(Unity);
		Three.pop_front();
		Three.pop_front();
	}

	//заполняем таблицу кодами в зависимости от частоты появления символа
	Node* root = Three.front();
	tableBuild(root, code2, table);

	//записываем содержимое исходного файла в новый файл с учётом новой кодировки
	std::ifstream infile2(in, std::ios_base::binary);
	if (!infile2.is_open()) {
		std::cout << "Some problems";
		return;
	}
	int countBit = 0;
	char buffer = (char)0;
	while (!infile2.eof()) {
		char chh = infile2.get();
		std::vector<bool> tmp = table.find(chh)->second;
		for (int i = 0; i < tmp.size(); ++i) {
			buffer += tmp[i] << (7 - countBit);
			++countBit;
			if (countBit == 8) {
				countBit = 0;
				outfile << buffer;
				buffer = (char)0;
			}
		}
	}
	delete root;
	outfile << buffer;
	infile2.close();
	outfile.close();
}
void dhuffman(std::ifstream& infile, std::ofstream& outfile) {
	std::vector<bool> code2; // бинарный код для заполнения табицы кодов(Хаффман)
	std::map<char, std::vector<bool>> table;// таблица кодов(Хаффман)
	//считываем количество байт в изначальном файле
	int quantity255 = 0;
	int lenChar = infile.get();
	int quantityOfCharInFile = 0;
	for (int i = 0; i < lenChar - 48; ++i) {
		int ch = infile.get();
		quantityOfCharInFile += ch << (lenChar - i - 1) * 8;
	}

	//считываем количество элементов с ненулевой частотой
	int numberOfSimvols = infile.get();
	if (numberOfSimvols == 0)
		numberOfSimvols = 256;

	//считываем частоту встречаемости каждого символа, создавая узлы для дерева с кодами
	std::list<Node*> Three;
	for (int i = 0; i < numberOfSimvols; ++i) {
		char simvol_ = infile.get();
		int len = infile.get() - 48;
		std::vector<char> quantity(0, len);
		int quantityInt = 0;
		for (int i = 0; i < len; ++i) {
			int ch = infile.get();
			quantityInt += ch << (len - i - 1) * 8;
		}
		if (simvol_ == (char)-1)
			quantity255 = quantityInt;
		Node* element = new Node;
		element->simvol_ = simvol_;
		element->weight_ = quantityInt;
		Three.push_back(element);
	}

	//создаём дерево, последовательно соединяя узлы с наименьшим весом
	while (Three.size() != 1) {
		Three.sort([](Node* left_, Node* right_) {return left_->weight_ < right_->weight_; });
		std::list<Node*>::iterator itr = Three.begin();
		Node* Unity = new Node;
		Unity->weight_ = (*itr)->weight_;
		Unity->left_ = *itr;
		++itr;
		Unity->weight_ += (*itr)->weight_;
		Unity->right_ = *itr;
		Three.push_back(Unity);
		Three.pop_front();
		Three.pop_front();
	}

	//заполняем его кодами
	Node* root = Three.front();
	tableBuild(root, code2, table);

	//разжимаем файл с учётом кодировки
	char ch = infile.get();
	int count = 0;
	int counterOfBite = 0;
	Node* ptr = root;
	while (!infile.eof()) {
		bool bit = ch & (1 << (7 - count));
		if (bit)
			ptr = ptr->right_;
		else
			ptr = ptr->left_;
		if ((ptr->left_ == NULL) && (ptr->right_ == NULL)) {
			outfile << ptr->simvol_;
			ptr = root;
			++counterOfBite;
			if (counterOfBite == quantityOfCharInFile - 1)
				break;
		}
		++count;
		if (count == 8) {
			count = 0;
			ch = infile.get();
		}
	}
	delete ptr;
}
void dlzw(std::ifstream& infile, std::ofstream& outfile) {
	//считываем количество байт в изначальном файле
	int lenChar = infile.get();
	int quantityOfCharInFile = 0;
	for (int i = 0; i < lenChar - 48; ++i) {
		int ch = infile.get();
		quantityOfCharInFile += ch << (lenChar - i - 1) * 8;
	}

	//проверяем является ли файл большим
	bool big_file = 0;
	if (quantityOfCharInFile > 110000)
		big_file = 1;


	//считываем весь файл в бинарный вектор
	std::vector<bool> binaryFile(quantityOfCharInFile * 8, 0);
	int fileIndex = 0;
	while (!infile.eof()) {
		char ch = infile.get();
		for (int j = 0; j < 8; ++j)
			binaryFile[fileIndex + j] = ((ch >> (8 - j - 1)) & 1);
		fileIndex += 8;
	}

	//создаём стандартный словарь
	std::map<int, std::string> reverseDictionary;
	// код слова, максимальное количество в слов(без изменения длины), длина кода в текущем словаре
	int binaryCode = 0;
	int lenghtCode = 8;
	int pow2 = 256;
	for (int i = 0; i < 256; ++i) {
		std::string element(1, (char)i);
		reverseDictionary[binaryCode] = element;
		++binaryCode;
	}

	// количество выведенных бит, количество выведенных байт
	int indexOutFile = 0;
	int countOfOut = 0;
	while (true) {
		//cчитываем количество бит равное размеру нынешней кодировки 
		int tmp = 0;
		for (int i = lenghtCode - 1; i >= 0; --i)
			tmp += binaryFile[indexOutFile + i] << (lenghtCode - i - 1);
		indexOutFile += lenghtCode;

		//получаем подстроку
		std::string tmpStr = reverseDictionary.find(tmp)->second;

		//проверяем словарь на переполнение и необходимость обновить длину бинарного кода
		if ((reverseDictionary.size() == 4096) && (big_file)) {
			reverseDictionary.clear();
			binaryCode = 0;
			lenghtCode = 8;
			for (int i = 0; i < 256; ++i) {
				std::string element(1, (char)i);
				reverseDictionary[binaryCode] = element;
				++binaryCode;
			}
			pow2 = 256;
		}
		if (reverseDictionary.size() == pow2) {
			pow2 *= 2;
			++lenghtCode;
		}

		//обновляем количество выведенных байт и сверяем с количеством байт в изначальном файле
		countOfOut += tmpStr.size();
		if (countOfOut >= quantityOfCharInFile) {
			if (tmpStr[tmpStr.size() - 1] == (char)-1)
				tmpStr.pop_back();
			break;
		}

		//считываем следующую подстроку
		int tmpNext = 0;
		for (int i = lenghtCode - 1; i >= 0; --i)
			tmpNext += binaryFile[indexOutFile + i] << (lenghtCode - i - 1);
		//создаём слудующий элемент с первым элементом новой подстроки
		std::string newElement(tmpStr.length() + 1, '0');
		if (reverseDictionary.find(tmpNext) == reverseDictionary.end()) {
			for (int index = 0; index < tmpStr.length(); ++index)
				newElement[index] = tmpStr[index];
			newElement[newElement.length() - 1] = tmpStr[0];
		}
		else {
			std::string tmpNextStr = reverseDictionary.find(tmpNext)->second;
			for (int index = 0; index < tmpStr.length(); ++index)
				newElement[index] = tmpStr[index];
			newElement[newElement.length() - 1] = tmpNextStr[0];
		}

		//добавляем в словарь
		reverseDictionary[binaryCode] = newElement;
		//увеличиваем бинарный код на 1, записываем в файл искомое слово
		++binaryCode;
		outfile << tmpStr;
	}
}
void lzw(const std::string& in, const std::string& out) {
	//сжатие lzw
	std::ifstream infile(in, std::ios_base::binary);
	if (!infile.is_open()) {
		std::cout << "Some problems";
		return;
	}

	std::map<std::string, int> dictionary; // словарь с кодами
	// код слова, максимальное количество в слов(без изменения длины), длина кода в текущем словаре
	int binaryCode = 0;
	int pow2 = 256;
	int lenghtCode = 8;
	//заносим стандартные символы в словарик
	for (int i = 0; i < 256; ++i) {
		std::string element(1, (char)i);
		dictionary[element] = binaryCode;
		++binaryCode;
	}

	//считываем количество символов в сжимаемом файле
	int counterBite = 0;
	char tmpChar;
	while (!infile.eof()) {
		tmpChar = infile.get();
		++counterBite;
	}

	//создаём бинарный вектор в который будем записывать результаты сжатия, считываем весь сжимаемый файл
	std::vector<bool> binaryStream(counterBite * 8, 0);
	bool flagBigFile = 0; // определяем является ли файл большим, влияет на степень сжатия
	if (counterBite > 110000)
		flagBigFile = 1;
	std::string str(counterBite, '0');
	infile.close();
	std::ifstream infile2(in, std::ios_base::binary);
	if (!infile2.is_open()) {
		std::cout << "Some problems";
		return;
	}
	int index = 0;
	while (!infile2.eof()) {
		str[index] = infile2.get();
		++index;
	}
	infile2.close();

	int indexOut = 0; // количество бит которое мы уже внесли в финальную бинарную строку
	for (int i = 0; i < str.length(); ++i) {
		int quantityOfExtraChar = 0;
		int length = 0; // сколько прибавляем символов, длина искомой строки
		std::map<std::string, int>::iterator itr;
		//находим максимальную подстроку имеющуюся в словаре
		while (true) {
			std::string strFind(quantityOfExtraChar + 1, '0');
			int index = 0;
			char charTmp;
			for (int j = i; j < i + quantityOfExtraChar + 1; ++j) {
				strFind[index] = str[j];
				++index;
			}
			if ((itr = dictionary.find(strFind)) == dictionary.end())
				break;
			length = strFind.length();
			++quantityOfExtraChar;
		}

		//заносим её код
		std::string maxStr(length, '0');
		for (int j = 0; j < length; ++j)
			maxStr[j] = str[i + j];
		itr = dictionary.find(maxStr);
		int itrCopyCode = itr->second;
		indexOut += lenghtCode;
		for (int i = 0; i < lenghtCode; ++i) {
			binaryStream[indexOut - i - 1] = itrCopyCode % 2;
			itrCopyCode /= 2;
		}

		//проверяем словарь на переполнение и необходимость обновить длину бинарного кода
		if ((binaryCode == 4096) && (flagBigFile)) {
			dictionary.clear();
			binaryCode = 0;
			for (int i = 0; i < 256; ++i) {
				std::string element(1, (char)i);
				dictionary[element] = binaryCode;
				++binaryCode;
			}
			pow2 = 256;
			lenghtCode = 8;
		}
		if (binaryCode == pow2) {
			pow2 *= 2;
			++lenghtCode;
		}

		//добавляем новую подстроку с первым элементом следующей подстроки 
		std::string newStr(length + 1, '0');
		for (int j = 0; j < length + 1; ++j)
			newStr[j] = str[i + j];
		//заносим элементе в словарик
		dictionary[newStr] = binaryCode;
		//увеличиваем бинарный код следующего элемента на 1
		++binaryCode;
		i += maxStr.size() - 1;
	}
	infile2.close();
	//записываем всё в файл
	std::ofstream outfile(out, std::ios_base::binary);
	if (!outfile.is_open()) {
		std::cout << "Some problems";
		return;
	}

	std::list<char> countOfBiteArr; // количество байт в сжимаемом файле
	while (counterBite > 0) {
		countOfBiteArr.push_front(counterBite % 256);
		counterBite /= 256;
	}
	outfile << '1' << countOfBiteArr.size(); // вносим ключ для lzw сжатия, и длину в байтах переменной: количество байт в сжимаемом файле
	auto itr = countOfBiteArr.begin();
	for (int i = 0; i < countOfBiteArr.size(); ++i, ++itr)//выводим количество байт в сжимаемом файле 
		outfile << *itr;
	int counter = 0;
	char tmp = 0;
	int outBit = 0;// количество выведенных бит
	//выводим нашу бинарную строку
	for (std::vector<bool>::iterator itr = binaryStream.begin(); itr != binaryStream.end(); ++itr) {
		if (outBit == indexOut)
			break;
		tmp += *itr << (7 - counter);
		++counter;
		if (counter == 8) {
			counter = 0;
			outfile << tmp;
			tmp = 0;
		}
		++outBit;
	}
	outfile << tmp;
	outfile.close();
}
int main(int argc, char* argv[]) {
	if (argc == 2) {
		std::string str = argv[1];
		if ((str == "?") || (str == "-h")) {
			setlocale(LC_ALL, "Russian");
			std::cout << "Вызов compress -lzw input output осуществляет сжатие файла input методом LZW и записывает результат в файл output." << std::endl;
			std::cout << "Вызов compress -huffman input output codes осуществляет сжатие файла input алгоритмом Хаффмана и записывает результат в файл output." << std::endl;
			std::cout << "Вызов compress -d huffman codes input output осуществляет декомпрессию файла input(закодированного по алгоритму Хаффмана) и записывает результат в файл output. Требует кодов для символов" << std::endl;
			std::cout << "Вызов compress -d lzw input output осуществляет декомпрессию файла input(закодированного по алгоритму LZW) и записывает результат в файл output." << std::endl;
		}
	}
	if (argc == 4) {
		std::string str = argv[1];
		if (str == "-lzw") {
			//сжатие lzw
			std::string in = argv[2];
			std::string out = argv[3];
			lzw(in, out);
		}
		else if (str == "-d") {
			std::string in = argv[2];
			std::string out = argv[3];
			std::ifstream infile(in, std::ios_base::binary);
			if (!infile.is_open()) {
				std::cout << "Some problems";
				return 0;
			}
			std::ofstream outfile(out, std::ios_base::binary);
			if (!outfile.is_open()) {
				std::cout << "Some problems";
				return 0;
			}
			char firstSim = infile.get(); //определяем как был сжат файл
			//распаковка lzw
			if (firstSim == '1')
				dlzw(infile, outfile);
			else if (firstSim == '0')
				dhuffman(infile, outfile);
			infile.close();
			outfile.close();
		}
		else if (str == "-huffman") {
			std::string in = argv[2];
			std::string out = argv[3];
			huffman(in, out);
		}
	}
}
