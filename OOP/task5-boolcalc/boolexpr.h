#pragma once
#include<algorithm> 
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<set>

int table(const char str);// функция сопоставляющая булевой операции приоритет выполнения
void incrimentBinnary(std::vector<bool>& code);// функция увиличивающая бинарный код на 1
std::string fromInfixToPostfix(const std::string& str);// функция переводящая инфиксную запись в постфиксную

class FormulaNode {
public:
	virtual bool calc() const = 0;
	virtual ~FormulaNode() {}
};

// класс узла константы
class NumNode : public FormulaNode {
	const bool num;
public:
	NumNode(double x) : num(x) { };
	bool calc() const { return num; };
};

// класс узла бинарной операции
class BinNode : public FormulaNode {
protected:
	FormulaNode* left, * right;
public:
	BinNode(FormulaNode* L, FormulaNode* R) : left(L), right(R) {}
	~BinNode() {
		delete left;
		delete right;
		left = right = nullptr;
	}
};

// класс узла конъюнкции
class ConjunctNode : public BinNode {
public:
	ConjunctNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return left->calc() & right->calc(); };
};

// класс узла дизъюнкции
class DinjunctNode : public BinNode {
public:
	DinjunctNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return left->calc() | right->calc(); };
};

// класс узла импликации
class ImplicNode : public BinNode {
public:
	ImplicNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return left->calc() <= right->calc(); };
};

// класс узла обратной импликации
class ReimplicNode : public BinNode {
public:
	ReimplicNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return left->calc() >= right->calc(); };
};

// класс узла суммы по модулю 2
class SummMod2Node : public BinNode {
public:
	SummMod2Node(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return (left->calc() + right->calc()) % 2; };
};

// класс узла равенства
class EqNode : public BinNode {
public:
	EqNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return left->calc() == right->calc(); };
};

// класс узла штриха Шеффера
class ShefferNode : public BinNode {
public:
	ShefferNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const {
		if ((left->calc()) && (right->calc()))
			return 0;
		else
			return 1;
	};
};

// класс узла стрелки Пирса
class PirsNode : public BinNode {
public:
	PirsNode(FormulaNode* L, FormulaNode* R) : BinNode(L, R) {}
	bool calc()const { return (((left->calc() == 0) && (right->calc() == 0)) ? 1 : 0); };
};

// класс узла унарной операции
class UnarNode : public FormulaNode {
protected:
	FormulaNode* next;
public:
	UnarNode(FormulaNode* node) : next(node) {}
	~UnarNode() { if (next) delete next; next = nullptr; }
};

// класс узла отрицание
class NotNode : public UnarNode {
public:
	NotNode(FormulaNode* node) : UnarNode(node) {}
	bool calc()const { if (next->calc()) return 0; else return 1; }
};

// класс узла переменной
class ParamValue {
	std::string ch_;
	bool val_;
public:
	ParamValue(const std::string& c, bool value) : ch_(c), val_(value) {}
	std::string getStr() const { return ch_; }
	bool getValue() const { return val_; }
	bool operator<(const ParamValue& X)const { return ch_ < X.ch_; }
	bool operator==(const ParamValue& X) const { return ch_ == X.ch_; }
};

//множество переменных с значениями
extern std::set<ParamValue> workspace;

//класс узла значения переменной
class ParamNode : public FormulaNode {
	std::string ch_;
public:
	ParamNode(const std::string& s ) : ch_(s) { }
	bool calc() const;
};

// класс булева выражения
class BooleanExpression {
private:
	std::string infixRecord_;// инфиксная запись
	FormulaNode* three_; // древо вычисления
	std::vector<std::string> variables_; // cписок переменных
public:
	FormulaNode* getThree() const { return three_; }
	std::vector<std::string> getValue() const { return variables_; }
	BooleanExpression(const char* infixRecord_d);
	bool calc() { return three_->calc(); };
	std::string cnf(); // построение КНФ
	std::string dnf();// построение ДНФ
	void truthTable(); // построение таблицы истинности
	void truthTable(std::ofstream& outputFile); // вывод таблицы истинности в указанный файл
	std::string zhegalkin() const;// построение полинома Жегалкина
	operator std::string() const { return infixRecord_; }
};
