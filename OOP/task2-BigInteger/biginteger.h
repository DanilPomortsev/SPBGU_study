#include <string>
#include<iostream>

static const long long N = 1000000000; //Основание используемой системы счисления
class BigInteger {
	unsigned int* ptrNumber_; // массив с разрядами
	int length_; // длина массива
	bool znak_; // знак
public:
	BigInteger();
	BigInteger(int number);
	BigInteger(unsigned int number);
	BigInteger(long number);
	BigInteger(unsigned long number);
	BigInteger(unsigned long long number);
	BigInteger(long long number);
	BigInteger(std::string const& str);
	BigInteger(const BigInteger& right);
	BigInteger(BigInteger&& right);
	const unsigned int* getPtr() const { return ptrNumber_; }
	int getLen() const { return length_; }
	bool getZnak() const { return znak_; }
	BigInteger& operator=(const BigInteger& right);
	BigInteger& operator=(BigInteger&& right);
	friend bool operator==(const BigInteger& left, const BigInteger& right);
	friend bool operator<(const BigInteger& left, const BigInteger& right);
	// все остальные ссылаются на равенство и больше
	friend bool operator!=(const BigInteger& left, const BigInteger& right);
	friend bool operator>(const BigInteger& left, const BigInteger& right);
	friend bool operator>=(const BigInteger& left, const BigInteger& right);
	friend bool operator<=(const BigInteger& left, const BigInteger& right);
	// оператор для орентирования по десятичным разрядам числа
	unsigned int operator[](unsigned int n) const;

	//функция занимающая у ближайшего ненулевого разряда еденицу(для разности)
	void zaim(int cur, unsigned int* number);

	// операции сложения
	friend const BigInteger operator+(const BigInteger& right);
	friend const BigInteger operator+(const BigInteger& left, const BigInteger& right);
	BigInteger& operator+=(const BigInteger& right);
	const BigInteger operator++();
	const BigInteger operator++(int);

	// операции разности
	friend const BigInteger operator-(const BigInteger& right);
	friend const BigInteger operator-(const BigInteger& left, const BigInteger& right);
	BigInteger& operator-=(const BigInteger& right);
	const BigInteger operator--();
	const BigInteger operator--(int);

	// операции умножения
	friend const BigInteger operator*(const BigInteger& left, const BigInteger& right);
	BigInteger& operator*=(BigInteger right);

	// операции деления 
	friend const BigInteger operator/(const BigInteger& left, const BigInteger& right);
	BigInteger& operator/=(const BigInteger& right);

	// операции остаток от деления
	friend const BigInteger operator%(const BigInteger& left, const BigInteger& right);
	BigInteger& operator%=(const BigInteger& right);

	//битовые смещения
	friend const BigInteger operator>>(const BigInteger& left, const BigInteger& right);
	BigInteger& operator>>=(const BigInteger& right);
	BigInteger& operator>>=(long long right);
	friend const BigInteger operator<<(const BigInteger& left, const BigInteger& right);
	BigInteger& operator<<=(const BigInteger& right);
	BigInteger& operator<<=(long long right);

	// операции конъюнкция
	friend const BigInteger operator&(const BigInteger& left, const BigInteger& right);
	BigInteger& operator&=(const BigInteger& right);


	// операции дизъюнкция
	friend const BigInteger operator|(const BigInteger& left, const BigInteger& right);
	BigInteger& operator|=(const BigInteger& right);

	//битовое отрицание
	BigInteger operator~();

	//исключающее или
	friend const BigInteger operator^(const BigInteger& left, const BigInteger& right);
	BigInteger& operator^=(const BigInteger& right);

	// оператор вывода
	friend std::ostream& operator<<(std::ostream& os, const BigInteger& bi);
};


//перевод в строку
std::string to_string(BigInteger const& right);
