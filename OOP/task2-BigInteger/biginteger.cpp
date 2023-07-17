#include"biginteger.h"
std::string to_string(BigInteger const& right) {
	if ((right.getLen() == 1) && (right.getPtr()[0] == 0)) {
		return "0";
	}
	else {
		int len10 = (right.getLen() - 1) * 9;
		int number0 = right.getPtr()[0];
		int znak = right.getZnak();
		if (!znak)
			++len10;
		while (number0) {
			++len10;
			number0 /= 10;
		}
		std::string result(len10, '0');
		int i = 0;
		if (!znak) {
			result[0] = '-';
			++i;
			znak = 1;
		}
		else
			znak = 0;
		for (; i < len10; ++i)
			result[i] = (char)(right[i - znak + 1] + 48);
		return result;
	}
}
BigInteger::BigInteger() {
	ptrNumber_ = new unsigned int[1];
	ptrNumber_[0] = 0;
	length_ = 1;
	znak_ = 1;
}
BigInteger::BigInteger(int number) {
	if (number == 0) {
		length_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
		znak_ = 1;
	}
	else {
		// определяем знак и взависимости от значения числа выделяем либо один разряд, либо два
		if (number >= 0)
			znak_ = 1;
		else {
			znak_ = 0;
			number *= -1;
		}
		if (number >= N) {
			length_ = 2;
			ptrNumber_ = new unsigned int[length_];
			ptrNumber_[0] = number / N;
			ptrNumber_[1] = number % N;
		}
		else {
			length_ = 1;
			ptrNumber_ = new unsigned int[length_];
			ptrNumber_[0] = number;
		}
	}
}
BigInteger::BigInteger(unsigned int number) {
	if (number == 0) {
		length_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
		znak_ = 1;
	}
	else {
		// определяем знак и взависимости от значения числа выделяем либо один разряд, либо два
		if (number >= 0)
			znak_ = 1;
		else {
			znak_ = 0;
			number *= -1;
		}
		if (number >= N) {
			length_ = 2;
			ptrNumber_ = new unsigned int[length_];
			ptrNumber_[0] = number / N;
			ptrNumber_[1] = number % N;
		}
		else {
			length_ = 1;
			ptrNumber_ = new unsigned int[length_];
			ptrNumber_[0] = number;
		}
	}
}
BigInteger::BigInteger(long number) {
	if (number == 0) {
		length_ = 1;
		znak_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
	}
	else {
		// определяем знак, определяем количество разрядов и заполняем их
		if (number > 0)
			znak_ = 1;
		else {
			znak_ = 0;
			number *= -1;
		}
		length_ = 0;
		long number_ = number;
		long number__ = number;
		if (number__ < 0)
			number__ *= -1;
		while (number_) {
			number_ /= N;
			++length_;
		}
		int i = length_ - 1;
		int length_Copy = length_;
		ptrNumber_ = new unsigned int[length_];
		while (number__) {
			ptrNumber_[i] = number__ % N;
			number__ /= N;
			--i;
		}
		while (ptrNumber_[0] == 0) {
			++ptrNumber_;
			--length_;
		}
	}
}
BigInteger::BigInteger(unsigned long number) {
	if (number == 0) {
		length_ = 1;
		znak_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
	}
	else {
		// определяем знак, определяем количество разрядов и заполняем их
		if (number > 0)
			znak_ = 1;
		else {
			znak_ = 0;
			number *= -1;
		}
		length_ = 0;
		unsigned long number_ = number;
		unsigned long number__ = number;
		if (number__ < 0)
			number__ *= -1;
		while (number_) {
			number_ /= N;
			++length_;
		}
		int i = length_ - 1;
		int length_Copy = length_;
		ptrNumber_ = new unsigned int[length_];
		while (number__) {
			ptrNumber_[i] = number__ % N;
			number__ /= N;
			--i;
		}
		while (ptrNumber_[0] == 0) {
			++ptrNumber_;
			--length_;
		}
	}
}
BigInteger::BigInteger(unsigned long long number) {
	if (number == 0) {
		length_ = 1;
		znak_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
	}
	else {
		// определяем знак, определяем количество разрядов и заполняем их
		if (number > 0)
			znak_ = 1;
		else {
			znak_ = 0;
			number *= -1;
		}
		length_ = 0;
		unsigned long long number_ = number;
		unsigned long long number__ = number;
		while (number_) {
			number_ /= N;
			++length_;
		}
		int i = length_ - 1;
		int length_Copy = length_;
		ptrNumber_ = new unsigned int[length_];
		while (number__) {
			ptrNumber_[i] = number__ % N;
			number__ /= N;
			--i;
		}
		while (ptrNumber_[0] == 0) {
			++ptrNumber_;
			--length_;
		}
	}
}
BigInteger::BigInteger(long long number) {
	if (number == 0) {
		length_ = 1;
		znak_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
	}
	else {
		// определяем знак, определяем количество разрядов и заполняем их
		if (number > 0)
			znak_ = 1;
		else {
			znak_ = 0;
			number *= -1;
		}
		length_ = 0;
		long long number_ = number;
		long long number__ = number;
		if (number__ < 0)
			number__ *= -1;
		while (number_) {
			number_ /= N;
			++length_;
		}
		int i = length_ - 1;
		int length_Copy = length_;
		ptrNumber_ = new unsigned int[length_];
		while (number__) {
			ptrNumber_[i] = number__ % N;
			number__ /= N;
			--i;
		}
		while (ptrNumber_[0] == 0) {
			++ptrNumber_;
			--length_;
		}
	}
}
BigInteger::BigInteger(std::string const& str) {
	if (str == "0") {
		length_ = 1;
		znak_ = 1;
		ptrNumber_ = new unsigned int[length_];
		ptrNumber_[0] = 0;
	}
	else {
		// проверяем на корректность данных
		if (str == "")
			throw std::invalid_argument("");
		for (int i = 0; i < str.length(); ++i) {
			if ((((str[i] < '0') || (str[i] > '9')) && (str[i] != '-')) || (str == "-") || ((str[i] == '-') && (i != 0)))
				throw std::invalid_argument("");
		}
		if (str[0] == '-') {
			if ((str[1] == '0') && (str.length() == 2)) {
				length_ = 1;
				znak_ = 0;
				ptrNumber_ = new unsigned int[1];
				ptrNumber_[0] = 0;
			}
			else {
				// из за того что система счисления кратна 10 считываем в разряд 9 чисел из строчки
				length_ = ((str.length() - 1) / 9) + 1;
				int start = (str.length() - 1) % 9;
				znak_ = 0;
				ptrNumber_ = new unsigned int[length_];
				for (int i = 0; i < length_; ++i) {
					ptrNumber_[i] = 0;
					unsigned long long multip = 1;
					if (i == 0)
						for (int j = start; j >= 1; --j) {
							ptrNumber_[i] += (str[j] - 48) * multip;
							multip *= 10;
						}
					else {
						for (int j = 8; j >= 0; --j) {
							ptrNumber_[i] += (str[(i - 1) * 9 + j + start + 1] - 48) * multip;
							multip *= 10;
						}
					}
				}
				if (ptrNumber_[0] == 0) {
					++ptrNumber_;
					--length_;
				}
			}
		}
		else {
			length_ = (str.length() / 9) + 1;
			int start = str.length() % 9;
			if (str.length() % 9 == 0) {
				--length_;
				start = 9;
			}
			znak_ = 1;
			ptrNumber_ = new unsigned int[length_];
			for (int i = 0; i < length_; ++i) {
				ptrNumber_[i] = 0;
				unsigned long long multpipl = 1;
				if (i == 0)
					for (int j = start - 1; j >= 0; --j) {
						ptrNumber_[i] += (str[j] - 48) * multpipl;
						multpipl *= 10;
					}
				else {
					for (int j = 8; j >= 0; --j) {
						ptrNumber_[i] += (str[(i - 1) * 9 + j + start] - 48) * multpipl;
						multpipl *= 10;
					}
				}
			}
		}
	}
}
BigInteger::BigInteger(const BigInteger& right) {
	length_ = right.length_;
	ptrNumber_ = new unsigned int[right.length_];
	for (int i = 0; i < length_; ++i)
		ptrNumber_[i] = right.ptrNumber_[i];
	znak_ = right.znak_;

}
BigInteger::BigInteger(BigInteger&& right) {
	length_ = right.length_;
	ptrNumber_ = right.ptrNumber_;
	right.ptrNumber_ = nullptr;
	right.length_ = 0;
	znak_ = right.znak_;
}
BigInteger& BigInteger::operator=(const BigInteger& right) {
	if (this != &right) {
		if (length_ != 0)
			delete[] ptrNumber_;
		length_ = right.length_;
		ptrNumber_ = new unsigned int[length_];
		for (int i = 0; i < length_; ++i)
			ptrNumber_[i] = right.ptrNumber_[i];
		znak_ = right.znak_;
	}
	return *this;
}
BigInteger& BigInteger::operator=(BigInteger&& right) {
	if (this != &right) {
		delete[] ptrNumber_;
		length_ = right.length_;
		ptrNumber_ = right.ptrNumber_;
		znak_ = right.znak_;
		right.ptrNumber_ = nullptr;
		right.length_ = 0;
	}
	return *this;
}
bool operator==(const BigInteger& left, const BigInteger& right) {
	if ((left.length_ == 1) && (right.length_ == 1) && (left.ptrNumber_[0] == 0) && (right.ptrNumber_[0] == 0)) //проверка на 0
		return 1;
	if (left.length_ != right.length_) // проверка длины
		return 0;
	if (left.znak_ == right.znak_) {
		if (left.length_ != right.length_)
			return 0;
		else {
			for (int i = 0; i < left.length_; ++i) {
				if (left.ptrNumber_[i] != right.ptrNumber_[i])
					return 0;
			}
		}
		return 1;
	}
	else {
		// проверяем побитовое представление
		if ((left.znak_ == 1) && (right.znak_ == 0)) {
			BigInteger leftCopy = left;
			BigInteger maxRank = 1;
			while (leftCopy != 0) {
				maxRank *= 256;
				leftCopy /= 256;
			}
			if (left + (-right) == maxRank)
				return 1;
			else
				return 0;
		}
		else {
			BigInteger rightCopy = right;
			BigInteger maxRank = 1;
			while (rightCopy != 0) {
				maxRank *= 256;
				rightCopy /= 256;
			}
			if (right + (-left) == maxRank)
				return 1;
			else
				return 0;
		}
	}
}
bool operator<(const BigInteger& left, const BigInteger& right) {
	if (left.znak_ < right.znak_)
		return 1;
	else if ((left.znak_ == 1) && (right.znak_ == 1)) {
		if (left.length_ < right.length_)
			return 1;
		else if (left.length_ == right.length_) {
			for (int i = 0; i < left.length_; ++i) {
				if (left.ptrNumber_[i] < right.ptrNumber_[i])
					return 1;
				else if (left.ptrNumber_[i] == right.ptrNumber_[i])
					continue;
				else
					return 0;
			}
			return 0;
		}
		return 0;
	}
	else if ((left.znak_ == 0) && (right.znak_ == 0)) {
		if (left.length_ < right.length_)
			return 0;
		else if (left.length_ == right.length_) {
			for (int i = 0; i < left.length_; ++i) {
				if (left.ptrNumber_[i] > right.ptrNumber_[i])
					return 1;
				else if (left.ptrNumber_[i] == right.ptrNumber_[i])
					continue;
				else
					return 0;
			}
			return 0;
		}
		return 1;
	}
	return 0;
}
const BigInteger operator+(const BigInteger& left, const BigInteger& right) {
	if (left.znak_ == right.znak_) {// вариант когда знаки чисел одинаковы
		BigInteger result;
		int ostatok = 0;
		if (right.length_ >= left.length_) {// рассматриваем вариант когда правое число больше и выделяем на сумму на один разряд больше чем в правом с запасом
			result.length_ = right.length_ + 1;
			result.ptrNumber_ = new unsigned int[result.length_];
			for (int i = right.length_; i >= 0; --i)
				if (i >= right.length_ - left.length_ + 1) {
					result.ptrNumber_[i] = (right.ptrNumber_[i - 1] + left.ptrNumber_[i - 1 - right.length_ + left.length_] + ostatok) % N;
					if (right.ptrNumber_[i - 1] + left.ptrNumber_[i - 1 - (right.length_ - left.length_)] + ostatok >= N)
						ostatok = 1;
					else
						ostatok = 0;
				}
				else if (i == 0)
					result.ptrNumber_[i] = ostatok;
				else {
					result.ptrNumber_[i] = right.ptrNumber_[i - 1] + ostatok;
					ostatok = 0;
				}
		}
		else {// левое больше
			result.length_ = left.length_ + 1;
			result.ptrNumber_ = new unsigned int[result.length_];
			for (int i = left.length_; i >= 0; --i)
				if (i >= left.length_ - right.length_ + 1) {
					result.ptrNumber_[i] = (left.ptrNumber_[i - 1] + right.ptrNumber_[i - 1 + right.length_ - left.length_] + ostatok) % N;
					if (left.ptrNumber_[i - 1] + right.ptrNumber_[i - 1 - (left.length_ - right.length_)] + ostatok >= N)
						ostatok = 1;
					else
						ostatok = 0;
				}
				else if (i == 0)
					result.ptrNumber_[i] = ostatok;
				else {
					result.ptrNumber_[i] = left.ptrNumber_[i - 1] + ostatok;
					ostatok = 0;
				}
		}
		if (*(result.ptrNumber_) == 0) {// проверяем является ли первый разряд нулевым,т.к. выделяли с запасом
			++result.ptrNumber_;
			--result.length_;
		}
		result.znak_ = right.znak_;
		return result;
	}// если знаки другие ссылаемся на разность
	else if ((left.znak_ == 1) && (right.znak_ == 0)) {
		BigInteger copyRight = BigInteger(right);
		copyRight.znak_ = 1;
		return left - copyRight;
	}
	else {
		BigInteger copyLeft = BigInteger(left);
		copyLeft.znak_ = 1;
		return right - copyLeft;
	}
}
const BigInteger operator-(const BigInteger& left, const BigInteger& right) {
	if (left.znak_ == right.znak_) {// вариант когда знаки равны
		BigInteger leftCopy = BigInteger(left);
		BigInteger rightCopy = BigInteger(right);
		leftCopy.znak_ = 1;
		rightCopy.znak_ = 1;
		if (leftCopy > rightCopy) { // левое число больше выделяем столько же разрядов сколько в нём
			BigInteger result;
			result.length_ = left.length_;
			result.ptrNumber_ = new unsigned int[result.length_];
			int i = result.length_ - 1;
			for (; i >= leftCopy.length_ - rightCopy.length_; --i) {
				if (leftCopy.ptrNumber_[i] < rightCopy.ptrNumber_[i - leftCopy.length_ + rightCopy.length_]) {
					result.zaim(i, leftCopy.ptrNumber_); //занимаем у левого числа 
					result.ptrNumber_[i] = leftCopy.ptrNumber_[i] + N - rightCopy.ptrNumber_[i - leftCopy.length_ + rightCopy.length_];
				}
				else
					result.ptrNumber_[i] = leftCopy.ptrNumber_[i] - rightCopy.ptrNumber_[i - leftCopy.length_ + rightCopy.length_];
			}
			for (; i >= 0; --i)
				result.ptrNumber_[i] = leftCopy.ptrNumber_[i];
			while (result.ptrNumber_[0] == 0) {// проверяем первый разряд так как выделяли разряды с запасом
				++result.ptrNumber_;
				--result.length_;
			}
			result.znak_ = left.znak_;
			return result;
		}
		else {
			// аналогично только правое больше
			BigInteger result;
			result.length_ = rightCopy.length_;
			result.ptrNumber_ = new unsigned int[result.length_];
			int i = result.length_ - 1;
			for (; ((i >= rightCopy.length_ - leftCopy.length_) && (i >= 0)); --i) {
				if (rightCopy.ptrNumber_[i] < leftCopy.ptrNumber_[i - rightCopy.length_ + leftCopy.length_]) {
					result.zaim(i, rightCopy.ptrNumber_);
					result.ptrNumber_[i] = rightCopy.ptrNumber_[i] + N - leftCopy.ptrNumber_[i - rightCopy.length_ + leftCopy.length_];
				}
				else
					result.ptrNumber_[i] = rightCopy.ptrNumber_[i] - leftCopy.ptrNumber_[i - rightCopy.length_ + leftCopy.length_];
			}
			for (; i >= 0; --i)
				result.ptrNumber_[i] = rightCopy.ptrNumber_[i];
			while ((result.ptrNumber_[0] == 0) && (result.length_ != 1)) {
				++result.ptrNumber_;
				--result.length_;
			}
			result.znak_ = !left.znak_;
			return result;
		}
	}
	//в остальных случаях ссылаемся на сложение
	else if ((left.znak_ == 1) && (right.znak_ == 0)) {
		BigInteger rightCopy = BigInteger(right);
		rightCopy.znak_ = 1;
		return left + rightCopy;
	}
	else {
		BigInteger rightCopy = BigInteger(right);
		rightCopy.znak_ = 0;
		return left + rightCopy;
	}
}
const BigInteger operator*(const BigInteger& left, const BigInteger& right) {
	BigInteger result;
	for (int i = right.length_ - 1, rank = 1; i >= 0; --i, ++rank) {//перемножаем все разряды первого и второго числа, складывая ысё в резултат
		BigInteger prom; // промежуточное являющееся результатом умножения соответствующих разрядов
		prom.znak_ = 1;
		prom.length_ = left.length_ + rank;
		prom.ptrNumber_ = new unsigned int[prom.length_];
		for (int z = 0; z < prom.length_; ++z)
			prom.ptrNumber_[z] = 0;
		int rank_ = rank - 1;
		while (rank_ > 0) {
			prom.ptrNumber_[prom.length_ - rank_] = 0;
			--rank_;
		}
		int ostatok = 0;
		int i1 = right.length_ - i + 1;
		for (int j = left.length_ - 1; j >= 0; --j) {
			unsigned long long tmp1 = right.ptrNumber_[i];
			unsigned long long	tmp2 = left.ptrNumber_[j];
			unsigned long long tmp = tmp1 * tmp2 + ostatok;
			BigInteger tmp_(tmp);
			if (tmp_.length_ == 2) {
				prom.ptrNumber_[j - rank + i1] = tmp_.ptrNumber_[1];
				ostatok = tmp_.ptrNumber_[0];
			}
			else {
				prom.ptrNumber_[j - rank + i1] = tmp_.ptrNumber_[0];
				ostatok = 0;
			}
		}
		prom.ptrNumber_[0] = ostatok;
		if (prom.ptrNumber_[0] == 0) { // проверяем не является ли первй разряд нулевым
			++prom.ptrNumber_;
			--prom.length_;
		}
		result = result + prom;
	}
	if (right.znak_ == left.znak_)
		result.znak_ = 1;
	else
		result.znak_ = 0;
	return result;
}
const BigInteger operator/(const BigInteger& left, const BigInteger& right) {
	//считываем длину обоих чисел в десятичной системе счисления
	unsigned int rightLen10 = (right.length_ - 1) * 9;
	int leftLen10 = (left.length_ - 1) * 9;
	int right0Copy = right.ptrNumber_[0];
	int left0Copy = left.ptrNumber_[0];
	while (right0Copy) {
		++rightLen10;
		right0Copy /= 10;
	}
	while (left0Copy) {
		++leftLen10;
		left0Copy /= 10;
	}

	int leftLen10Start = leftLen10;
	bool flagStart = 1;
	int* array = new int[leftLen10]; //выделяем память как в левом числе т.к. результат не может получиться численно больше левого числа
	int posZapol = 0;
	BigInteger ost;
	int countZeros = 0;
	unsigned int ostLen10 = 0;
	BigInteger leftCopy = BigInteger(left);
	BigInteger rightCopy = BigInteger(right);
	leftCopy.znak_ = 1;
	rightCopy.znak_ = 1;
	// деление столбиком
	while (leftCopy >= rightCopy) {
		//считываем количество разрядов в текущем левом числе
		unsigned int leftLen10 = (leftCopy.length_ - 1) * 9;
		int left0Copy = leftCopy.ptrNumber_[0];
		while (left0Copy) {
			++leftLen10;
			left0Copy /= 10;
		}

		// определяем по какой десятичный разряд нам необходимо считывать левое число для вычетания
		int tekPos = 0;// разряд по который будем считывать, если идёт первая итерация то равно длине правого числа
		if (flagStart)
			tekPos = rightLen10 - 1;

		// увеличиваем tekPos пока prom не станет больше делителя(определяем по какой десятичный разряд нам необходимо считывать левое число для вычетания)
		BigInteger prom;
		while (prom < rightCopy) {
			if ((tekPos >= ostLen10 + 1) && (flagStart != 1)) {
				array[posZapol] = 0;
				++posZapol;
			}
			++tekPos;
			prom = 0;
			BigInteger mnojitel = 1;
			for (int i = tekPos; i >= 1; --i) {
				prom += leftCopy[i] * mnojitel;
				mnojitel *= 10;
			}
		}

		//определяем во сколько раз правое число меньше prom
		BigInteger right_ = rightCopy;
		int count = 0;
		while (right_ <= prom) {
			right_ = right_ + rightCopy;
			++count;
		}
		right_ = right_ - rightCopy;

		// проверяем случай когда они оказываются равными
		int tekPos_copy = tekPos;
		if (right_ == prom) {
			while ((tekPos_copy < leftLen10Start) && (leftCopy[tekPos_copy + 1] == 0)) {
				++countZeros;
				++tekPos_copy;
			}
		}

		ost = prom - right_;// остаток после вычетания
		unsigned int ost0 = ost.ptrNumber_[0];
		ostLen10 = 0;
		if (ost.length_ != 0) {
			while (ost0) {
				++ostLen10;
				ost0 /= 10;
			}
			ostLen10 += (ost.length_ - 1) * 9;
		}

		// умножаем правое число на нужное количество разрядов чтобы вычесть из левого
		for (int i = 0; i < leftLen10 - tekPos; ++i)
			right_ = right_ * 10;
		leftCopy -= right_; // вычетаем

		array[posZapol] = count;// на соответсвующее место в выделенном массиве ставим полученное кратное
		++posZapol;
		flagStart = 0;

		// проверяем количество незначащих нулей теперь
		while (countZeros) {
			array[posZapol] = 0;
			++posZapol;
			--countZeros;
		}
	}

	//получаме число BigInteger из массива с десятичными разрядами
	if (ost.length_ == 0)
		array[posZapol++] = 0;
	BigInteger result;
	BigInteger mnojitel(1);
	for (int i = posZapol - 1; i >= 0; --i) {
		BigInteger mnojitel_copy = mnojitel;
		result += mnojitel * array[i];
		mnojitel_copy = mnojitel_copy * 10;
		mnojitel = mnojitel_copy;
	}
	if (right.znak_ == left.znak_)
		result.znak_ = 1;
	else
		result.znak_ = 0;
	return result;
}
const BigInteger operator%(const BigInteger& left, const BigInteger& right) {
	// алгоритм тот же самый только нам нужен исключительно остаток
	unsigned int rightLen10 = 0;
	int right0 = right.ptrNumber_[0];
	while (right0) {
		++rightLen10;
		right0 /= 10;
	}
	unsigned int leftLen10 = 0;
	int left0 = left.ptrNumber_[0];
	while (left0) {
		++leftLen10;
		left0 /= 10;
	}
	BigInteger leftCopy = BigInteger(left);
	BigInteger rightCopy = BigInteger(right);
	leftCopy.znak_ = 1;
	rightCopy.znak_ = 1;
	leftLen10 += (leftCopy.length_ - 1) * 9;
	rightLen10 += (rightCopy.length_ - 1) * 9;
	int leftLen10Start = leftLen10;
	bool flagStart = 1;
	int* array = new int[leftLen10];

	while (leftCopy >= rightCopy) {
		unsigned int leftLen10 = 0;
		unsigned int left0 = leftCopy.ptrNumber_[0];
		while (left0) {
			++leftLen10;
			left0 /= 10;
		}
		leftLen10 += (leftCopy.length_ - 1) * 9;
		int tekPos = 0;
		if (flagStart)
			tekPos = rightLen10 - 1;
		BigInteger prom;
		while (prom < rightCopy) {
			++tekPos;
			prom = 0;
			int mnojitel = 1;
			for (int i = tekPos; i >= 1; --i) {
				prom += leftCopy[i] * mnojitel;
				mnojitel *= 10;
			}
		}
		BigInteger right_ = rightCopy;
		while (right_ <= prom)
			right_ = right_ + rightCopy;
		right_ = right_ - rightCopy;
		for (int i = 0; i < leftLen10 - tekPos; ++i)
			right_ = right_ * 10;
		leftCopy -= right_;
		flagStart = 0;
	}
	BigInteger result;
	result = leftCopy;
	result.znak_ = left.znak_;
	return result;
}
// все бинарные операции просто использование операции для соответствующих разрядов
const BigInteger operator&(const BigInteger& left, const BigInteger& right) {
	BigInteger result;
	bool leftFlag = 0;
	BigInteger leftCopy = left;
	BigInteger rightCopy = right;
	if (!left.znak_) {
		leftCopy.znak_ = 1;
		BigInteger maxRank = 1;
		while (leftCopy != 0) {
			leftCopy /= 256;
			maxRank *= 256;
		}
		leftCopy = maxRank - (-left);
	}
	if (!right.znak_) {
		rightCopy.znak_ = 1;
		BigInteger maxRank = 1;
		while (rightCopy != 0) {
			rightCopy /= 256;
			maxRank *= 256;
		}
		rightCopy = maxRank - (-right);
	}
	if (leftCopy.length_ >= rightCopy.length_) {
		result.length_ = leftCopy.length_;
		leftFlag = 1;
	}
	else
		result.length_;
	result.ptrNumber_ = new unsigned int[result.length_];
	if (leftFlag) {
		int i = 0;
		for (; i < rightCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] & rightCopy.ptrNumber_[i];
		for (; i < leftCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] & 0;
	}
	else {
		int i = 0;
		for (; i < leftCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] & rightCopy.ptrNumber_[i];
		for (; i < rightCopy.length_; ++i)
			result.ptrNumber_[i] = rightCopy.ptrNumber_[i] & 0;
	}
	while ((result.ptrNumber_[result.length_ - 1] == 0) && (result.length_ != 1))
		--result.length_;
	return result;
}
const BigInteger operator|(const BigInteger& left, const BigInteger& right) {
	BigInteger result;
	bool leftFlag = 0;
	BigInteger leftCopy = left;
	BigInteger rightCopy = right;
	if (!left.znak_) {
		leftCopy.znak_ = 1;
		BigInteger maxRank = 1;
		while (leftCopy != 0) {
			leftCopy /= 256;
			maxRank *= 256;
		}
		leftCopy = maxRank - (-left);
	}
	if (!right.znak_) {
		rightCopy.znak_ = 1;
		BigInteger maxRank = 1;
		while (rightCopy != 0) {
			rightCopy /= 256;
			maxRank *= 256;
		}
		rightCopy = maxRank - (-right);
	}
	if (leftCopy.length_ >= rightCopy.length_) {
		result.length_ = leftCopy.length_;
		leftFlag = 1;
	}
	else
		result.length_;
	result.ptrNumber_ = new unsigned int[result.length_];
	if (leftFlag) {
		int i = 0;
		for (; i < rightCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] | rightCopy.ptrNumber_[i];
		for (; i < leftCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] | 0;
	}
	else {
		int i = 0;
		for (; i < leftCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] | rightCopy.ptrNumber_[i];
		for (; i < rightCopy.length_; ++i)
			result.ptrNumber_[i] = rightCopy.ptrNumber_[i] | 0;
	}
	while ((result.ptrNumber_[result.length_ - 1] == 0) && (result.length_ != 1))
		--result.length_;
	return result;
}
BigInteger BigInteger::operator~() {
	BigInteger thisCopy;
	thisCopy = *this;
	if (thisCopy.znak_ == 1) {
		thisCopy.znak_ = 0;
		--thisCopy;
	}
	else {
		thisCopy.znak_ = 1;
		++thisCopy;
	}
	return thisCopy;
}
const BigInteger operator^(const BigInteger& left, const BigInteger& right) {
	BigInteger result;
	bool leftFlag = 0;
	BigInteger leftCopy = left;
	BigInteger rightCopy = right;
	if (!left.znak_) {
		leftCopy.znak_ = 1;
		BigInteger maxRank = 1;
		while (leftCopy != 0) {
			leftCopy /= 256;
			maxRank *= 256;
		}
		leftCopy = maxRank - (-left);
	}
	if (!right.znak_) {
		rightCopy.znak_ = 1;
		BigInteger maxRank = 1;
		while (rightCopy != 0) {
			rightCopy /= 256;
			maxRank *= 256;
		}
		rightCopy = maxRank - (-right);
	}
	if (leftCopy.length_ >= rightCopy.length_) {
		result.length_ = leftCopy.length_;
		leftFlag = 1;
	}
	else
		result.length_;
	result.ptrNumber_ = new unsigned int[result.length_];
	if (leftFlag) {
		int i = 0;
		for (; i < rightCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] ^ rightCopy.ptrNumber_[i];
		for (; i < leftCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] ^ 0;
	}
	else {
		int i = 0;
		for (; i < leftCopy.length_; ++i)
			result.ptrNumber_[i] = leftCopy.ptrNumber_[i] ^ rightCopy.ptrNumber_[i];
		for (; i < rightCopy.length_; ++i)
			result.ptrNumber_[i] = rightCopy.ptrNumber_[i] ^ 0;
	}
	while ((result.ptrNumber_[result.length_ - 1] == 0) && (result.length_ != 1))
		--result.length_;
	return result;
}
std::ostream& operator<<(std::ostream& os, const BigInteger& bi) {
	if (!bi.znak_)
		os << '-';
	if (bi.length_ == 1)
		os << bi.ptrNumber_[0];
	else {
		for (int i = 0; i < bi.length_; ++i) {
			if (i != 0) {
				int currentRankLen = 0;
				int copy = bi.ptrNumber_[i];
				while (copy) {
					++currentRankLen;
					copy /= 10;
				}
				for (int j = 0; j < 9 - currentRankLen; ++j)
					os << 0;
			}
			os << bi.ptrNumber_[i];
		}
	}
	return os;
}
void BigInteger::zaim(int cur, unsigned int* number) {
	int j = cur - 1;
	while (number[j] == 0)
		--j;
	--number[j];
	++j;
	while (j != cur) {
		number[j] = N - 1;
		++j;
	}
}
bool operator!=(const BigInteger& left, const BigInteger& right) {
	return !(left == right);
}
bool operator>(const BigInteger& left, const BigInteger& right) {
	if (left == right)
		return 0;
	else
		return !(left < right);
}
bool operator>=(const BigInteger& left, const BigInteger& right) {
	return ((left == right) || (left > right));
}
bool operator<=(const BigInteger& left, const BigInteger& right) {
	return ((left == right) || (left < right));
}
const BigInteger operator+(const BigInteger& right) {
	return right;
}
BigInteger& BigInteger::operator+=(const BigInteger& right) {
	return *this = *this + right;
}
const BigInteger BigInteger::operator++() {
	return *this = *this + 1;
}
const BigInteger BigInteger::operator++(int) {
	BigInteger thisPast = *this;
	*this += 1;
	return thisPast;
}
unsigned int BigInteger::operator[](unsigned int n) const {
	int lenIn10 = 0;
	int firstRankCopy = ptrNumber_[0];
	lenIn10 += 9 * (length_ - 1);
	while (firstRankCopy) {
		firstRankCopy /= 10;
		++lenIn10;
	}
	int firstRankLen = lenIn10 % 9;
	if (firstRankLen == 0)
		firstRankLen = 9;
	if (n <= firstRankLen) {
		unsigned int rank = ptrNumber_[0];
		for (int i = 0; i < firstRankLen - n; ++i)
			rank /= 10;
		return rank % 10;
	}
	else {
		n -= firstRankLen;
		int rankN = n / 9 + 1, rankInRank = n % 9;
		if (rankInRank == 0) {
			rankInRank = 9;
			--rankN;
		}
		n = n % 9;
		if (n == 0)
			n = 9;
		unsigned int rank = ptrNumber_[rankN];
		for (int i = 0; i < 9 - n; ++i)
			rank /= 10;
		return rank % 10;
	}
}
const BigInteger operator-(const BigInteger& right) {
	BigInteger copy;
	copy = right;
	if (copy.znak_)
		copy.znak_ = 0;
	else
		copy.znak_ = 1;
	return copy;
}
BigInteger& BigInteger::operator-=(const BigInteger& right) {
	return *this = *this - right;
}
const BigInteger BigInteger::operator--() {
	return *this = *this - 1;
}
const BigInteger BigInteger::operator--(int) {
	BigInteger thisPast = *this;
	*this -= 1;
	return thisPast;
}
BigInteger& BigInteger::operator*=(BigInteger right) {
	return *this = *this * right;
}
BigInteger& BigInteger::operator/=(const BigInteger& right) {
	return *this = *this / right;
}
BigInteger& BigInteger::operator%=(const BigInteger& right) {
	return *this = *this % right;
}
const BigInteger operator>>(const BigInteger& left, const BigInteger& right) {
	BigInteger result;
	result = left;
	BigInteger pow2 = 1;
	for (BigInteger i; i < right; ++i)
		pow2 *= 2;
	result /= pow2;
	if (left.znak_ == 0)
		--result;
	return result;
}
BigInteger& BigInteger::operator>>=(const BigInteger& right) {
	return *this = *this >> right;
}
BigInteger& BigInteger::operator>>=(long long right) {
	BigInteger right_(right);
	return *this = *this >> right_;
}
const BigInteger operator<<(const BigInteger& left, const BigInteger& right) {
	BigInteger result;
	result = left;
	for (BigInteger i; i < right; ++i)
		result *= 2;
	return result;
}
BigInteger& BigInteger::operator<<=(const BigInteger& right) {
	return *this = *this << right;
}
BigInteger& BigInteger::operator<<=(long long right) {
	BigInteger right_(right);
	return *this = *this << right_;
}
BigInteger& BigInteger::operator&=(const BigInteger& right) {
	return *this = *this & right;
}
BigInteger& BigInteger::operator|=(const BigInteger& right) {
	return *this = *this | right;
}
BigInteger& BigInteger::operator^=(const BigInteger& right) {
	return *this = *this ^ right;
}
