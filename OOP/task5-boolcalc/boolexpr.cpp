#include"boolexpr.h"
#include<cstring>
#include<cmath>
// функция сопоставляющая булевой операции приоритет выполнения
int table(const char str) {
	switch (str)
	{
	case '~':
		return 4;
		break;
	case '&':
		return 3;
		break;
	case 'v':
		return 2;
		break;
	case '+':
		return 2;
		break;
	case '>':
		return 1;
		break;
	case '<':
		return 1;
		break;
	default:
		return 0;
		break;
	}
}
// функция увиличивающая бинарный код на 1
void incrimentBinnary(std::vector<bool>& code) {
	if (code[code.size() - 1] == 0) {
		code[code.size() - 1] = 1;
		return;
	}
	else {
		int i = code.size() - 1;
		do {
			code[i] = 0;
			--i;
			if (i == -1)
				return;
			if (i == 0)
				break;
		} while (code[i] == 1);
		code[i] = 1;
		return;
	}
}
// функция переводящая инфиксную запись в постфиксную
std::string fromInfixToPostfix(const std::string& str) {
	int count = 0;
	int countX = 0;
	int j = 0;
	for (int i = 0; i < str.length(); ++i) {
		if ((str[i] == ')') || (str[i] == '(') || (str[i] == ' '))
			++count;
		if (str[i] == 'x')
			++countX;
	}
	std::string result(str.length() - count + countX + 1, '0');
	std::vector<char> stack;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ' ')
			continue;
		else if ((str[i] != '&') && (str[i] != 'v') && (str[i] != '>') && (str[i] != '<') && (str[i] != '+') && (str[i] != '=')
			&& (str[i] != '^') && (str[i] != '|') && (str[i] != ')') && (str[i] != '(')) {
			if (str[i] != '~') {
				while ((str[i] != ' ') && (str[i] != '&') && (str[i] != 'v') && (str[i] != '>') && (str[i] != '<') && (str[i] != '+')
					&& (str[i] != '=') && (str[i] != '^') && (str[i] != '|') && (str[i] != ')') && (str[i] != '(')) {
					if (i == str.length())
						break;
					result[j] = str[i];
					++i;
					++j;
				}
				--i;
				result[j] = ' ';
				++j;
			}
			else
				stack.push_back('~');
		}
		else if ((str[i] == '&') || (str[i] == 'v') || (str[i] == '>') || (str[i] == '<') || (str[i] == '+') || (str[i] == '=')
			|| (str[i] == '^') || (str[i] == '|')) {
			if (stack.size() == 0)
				stack.push_back(str[i]);
			else if (table(str[i]) > table(stack[stack.size() - 1]))
				stack.push_back(str[i]);
			else {
				while (table(str[i]) <= table(stack[stack.size() - 1])) {
					result[j] = stack[stack.size() - 1];
					++j;
					stack.pop_back();
					if (stack.size() == 0)
						break;
				}
				stack.push_back(str[i]);
			}
		}
		else if (str[i] == '(')
			stack.push_back('(');
		else if (str[i] == ')') {
			while (stack[stack.size() - 1] != '(') {
				result[j] = stack[stack.size() - 1];
				stack.pop_back();
				++i;
				++j;
			}
			--i;
			stack.pop_back();
		}
	}
	while (stack.size() != 0) {
		result[j] = stack[stack.size() - 1];
		stack.pop_back();
		++j;
	}
	return result;
}
// функция вычисления значения переменной
bool ParamNode::calc() const {
	auto pos0 = workspace.find(ParamValue(ch_, 0));
	if (pos0 != workspace.end())
		return (*pos0).getValue();
	else {
		bool tmp;
		std::cout << ch_ << " = ";
		std::cin >> tmp;
		std::cin.ignore();
		workspace.insert(ParamValue(ch_, tmp));
		return tmp;
	}
}
BooleanExpression::BooleanExpression(const char* infixRecord_d) {
	try {
		infixRecord_ = std::string(strlen(infixRecord_d), '0');
		bool lastIsX = 0;
		bool lastIsOperator = 0;
		bool lastIsConst = 0;
		int countOfBrakers = 0;
		// проверяем накорректность входных данных
		for (int i = 0; i < strlen(infixRecord_d); ++i) {
			if (infixRecord_d[i] == 'x') {
				if ((lastIsX) || (lastIsConst))
					throw 1;
				lastIsX = 1;
				lastIsOperator = 0;
				lastIsConst = 0;
			}
			else if ((infixRecord_d[i] == '&') || (infixRecord_d[i] == 'v') || (infixRecord_d[i] == '>') || (infixRecord_d[i] == '<') || (infixRecord_d[i] == '+')
				|| (infixRecord_d[i] == '=') || (infixRecord_d[i] == '^') || (infixRecord_d[i] == '|')) {
				if (lastIsOperator)
					throw 1;
				lastIsOperator = 1;
				lastIsX = 0;
				lastIsConst = 0;
			}
			else if (infixRecord_d[i] == '(')
				++countOfBrakers;
			else if (infixRecord_d[i] == ')')
				--countOfBrakers;
			else if ((lastIsOperator) && (infixRecord_d[i] >= '0') && (infixRecord_d[i] <= '9')) {
				if ((lastIsConst) || (lastIsX))
					throw 1;
				if ((int)infixRecord_d[i] > 49)
					throw 1;
				else {
					lastIsConst = 1;
					lastIsOperator = 0;
					lastIsX = 0;
				}
			}
		}
		if ((countOfBrakers != 0) || (lastIsOperator))
			throw 1;
		for (int i = 0; i < strlen(infixRecord_d); ++i)
			infixRecord_[i] = infixRecord_d[i];
		std::string postfixRecord = fromInfixToPostfix(infixRecord_);

		// составляем дерево из постфиксной записи
		FormulaNode* result;
		FormulaNode* right;
		FormulaNode* left;
		std::vector<FormulaNode*> arrray;
		for (int i = 0; i < postfixRecord.length(); ++i) {
			char ch = postfixRecord[i];
			switch (ch) {
			case('&'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new ConjunctNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('v'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new DinjunctNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('>'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new ImplicNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('<'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new ReimplicNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('+'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new SummMod2Node(left, right);
					arrray.push_back(result);
					break;
				}
			case('='):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new EqNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('|'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new ShefferNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('^'):
				if (arrray.size() >= 2) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					left = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new PirsNode(left, right);
					arrray.push_back(result);
					break;
				}
			case('~'):
				if (arrray.size() >= 1) {
					right = arrray[arrray.size() - 1];
					arrray.pop_back();
					result = new NotNode(right);
					arrray.push_back(result);
					break;
				}
			default:
				if ((ch == '1') || (ch == '0')) {
					result = new NumNode(int(ch - 48));
					arrray.push_back(result);
				}
				else if ((ch != '&') && (ch != 'v') && (ch != '>') && (ch != '<') && (ch != '+') && (ch != '=') && (ch != '^') && (ch != '|') && (ch != ')') && (ch != '(')) {
					int len = 0;
					while (postfixRecord[i] != ' ') {
						++i;
						++len;
					}
					int end = i;
					int j = 0;
					i -= len;
					std::string variable(len, 'l');
					while (i != end) {
						variable[j] = postfixRecord[i];
						++i;
						++j;
					}
					result = new ParamNode(variable);
					arrray.push_back(result);
				}
			}
		}
		three_ = arrray[0];

		// заполняем список переменных
		for (int i = 0; i < postfixRecord.length(); ++i) {
			if (postfixRecord[i] == 'x') {
				std::string tmp;
				while ((postfixRecord[i] != ' ') && (postfixRecord[i] != '\0')) {
					tmp.push_back(postfixRecord[i]);
					++i;
				}
				if (variables_.size() == 0)
					variables_.push_back(tmp);
				else {
					bool globalFlag = 1;
					for (int i = 0; i < variables_.size(); ++i) {
						bool eqFlag = 1;
						if (variables_[i].size() != tmp.size())
							eqFlag = 0;
						else {
							for (int j = 0; j < variables_[i].size(); ++j) {
								if (variables_[i][j] != tmp[j]) {
									eqFlag = 0;
									break;
								}
							}
						}
						if (eqFlag == 1) {
							globalFlag = 0;
							break;
						}
					}
					if (globalFlag == 1)
						variables_.push_back(tmp);
				}
			}
		}
		std::sort(variables_.begin(), variables_.end());
	}
	catch (...) {
		std::cout << "incorrect source data. it is not possible to form an expression";
	}
}
std::string BooleanExpression::cnf() {
	workspace.clear();
	std::vector<bool> values(variables_.size(), 0);
	std::vector<std::vector<bool>> requiredValues;
	int pow = 1 << variables_.size();
	// перебираем все значения переменных и отбирраем только нужные нам значения
	for (int i = 0; i < pow; ++i) {
		for (int j = 0; j < variables_.size(); ++j)
			workspace.insert(ParamValue(variables_[j], values[j]));
		if (three_->calc() == 0)
			requiredValues.push_back(values);
		workspace.clear();
		incrimentBinnary(values);
	}

	//создаём строчку под КНФ
	int maxSize = 0;
	for (int i = 0; i < variables_.size(); ++i) {
		if (variables_[i].length() > maxSize)
			maxSize = variables_[i].length();
	}
	std::string result((values.size() * maxSize + 3 + values.size()) * requiredValues.size() + requiredValues.size() - 1, '0');

	// записываем её
	int i = 0;
	for (int j = 0; j < requiredValues.size(); ++j) {
		result[i] = '(';
		++i;
		for (int l = 0; l < values.size(); ++l) {
			if (requiredValues[j][l] == 1) {
				result[i] = '~';
				++i;
			}
			for (int m = 0; m < variables_[l].length(); ++m) {
				result[i] = variables_[l][m];
				++i;
			}
			if (l != values.size() - 1) {
				result[i] = 'v';
				++i;
			}
		}
		result[i] = ')';
		++i;
		if (j != requiredValues.size() - 1) {
			result[i] = '&';
			++i;
		}
	}
	while (result[result.length() - 1] == '0')
		result.pop_back();
	return result;
}
std::string BooleanExpression::dnf() {
	workspace.clear();
	std::vector<bool> values(variables_.size(), 0);
	std::vector<std::vector<bool>> requiredValues;
	int pow = 1 << variables_.size();
	// перебираем все значения переменных и отбирраем только нужные нам значения
	for (int i = 0; i < pow; ++i) {
		for (int j = 0; j < variables_.size(); ++j)
			workspace.insert(ParamValue(variables_[j], values[j]));
		if (three_->calc() == 1)
			requiredValues.push_back(values);
		workspace.clear();
		incrimentBinnary(values);
	}

	//создаём строчку под ДНФ
	int maxSize = 0;
	for (int i = 0; i < variables_.size(); ++i) {
		if (variables_[i].length() > maxSize)
			maxSize = variables_[i].length();
	}
	std::string result((values.size() * maxSize + 3 + values.size()) * requiredValues.size() + requiredValues.size() - 1, '0');

	// записываем её
	int i = 0;
	for (int j = 0; j < requiredValues.size(); ++j) {
		result[i] = '(';
		++i;
		for (int l = 0; l < values.size(); ++l) {
			if (requiredValues[j][l] == 0) {
				result[i] = '~';
				++i;
			}
			for (int m = 0; m < variables_[l].length(); ++m) {
				result[i] = variables_[l][m];
				++i;
			}
			if (l != values.size() - 1) {
				result[i] = '&';
				++i;
			}
		}
		result[i] = ')';
		++i;
		if (j != requiredValues.size() - 1) {
			result[i] = 'v';
			++i;
		}
	}
	while (result[result.length() - 1] == '0')
		result.pop_back();
	return result;
}
void BooleanExpression::truthTable() {
	if ((this->infixRecord_ == "1") || (this->infixRecord_ == "0"))
		std::cout << bool(this->infixRecord_[0] - 48);
	else {
		// выводим переменные
		std::cout << '|';
		for (int i = 0; i < variables_.size(); ++i)
			std::cout << variables_[i] << '|';
		std::cout << infixRecord_ << '|' << std::endl;
		workspace.clear();
		std::vector<bool> values(variables_.size(), 0);
		int pow = 1 << variables_.size();

		// перебираем все возможные значения переменных в векторе values и выводи значение выражения при этих значениях переменных
		for (int i = 0; i < pow; ++i) {
			for (int j = 0; j < variables_.size(); ++j)
				workspace.insert(ParamValue(variables_[j], values[j]));
			std::cout << "|";
			for (int j = 0; j < variables_.size(); ++j) {
				bool start = 1;
				for (int l = 0; l < variables_[j].size(); ++l) {
					if (l < variables_[j].size() / 2)
						std::cout << ' ';
					else {
						if (start) {
							std::cout << values[j];
							start = 0;
						}
						else
							std::cout << ' ';
					}
				}
				std::cout << '|';
			}
			bool start = 1;
			for (int j = 0; j < infixRecord_.size(); ++j) {
				if (j < infixRecord_.size() / 2)
					std::cout << ' ';
				else {
					if (start) {
						std::cout << three_->calc();
						start = 0;
					}
					else
						std::cout << ' ';
				}
			}
			std::cout << '|' << std::endl;
			workspace.clear();
			incrimentBinnary(values);
		}
	}
}
void BooleanExpression::truthTable(std::ofstream& outputFile) {
	if ((infixRecord_ == "1") || (infixRecord_ == "0"))
		outputFile << bool(infixRecord_[0] - 48);
	else {
		// выводим переменные
		outputFile << '|';
		for (int i = 0; i < variables_.size(); ++i)
			outputFile << variables_[i] << '|';
		outputFile << infixRecord_ << '|' << std::endl;
		workspace.clear();
		std::vector<bool> values(variables_.size(), 0);
		int pow = 1 << variables_.size();

		// перебираем все возможные значения переменных в векторе values и выводи значение выражения при этих значениях переменных
		for (int i = 0; i < pow; ++i) {
			for (int j = 0; j < variables_.size(); ++j)
				workspace.insert(ParamValue(variables_[j], values[j]));
			outputFile << "|";
			for (int j = 0; j < variables_.size(); ++j) {
				bool start = 1;
				for (int l = 0; l < variables_[j].size(); ++l) {
					if (l < variables_[j].size() / 2)
						outputFile << ' ';
					else {
						if (start) {
							outputFile << values[j];
							start = 0;
						}
						else
							outputFile << ' ';
					}
				}
				outputFile << '|';
			}
			bool start = 1;
			for (int j = 0; j < infixRecord_.size(); ++j) {
				if (j < infixRecord_.size() / 2)
					outputFile << ' ';
				else {
					if (start) {
						outputFile << three_->calc();
						start = 0;
					}
					else
						outputFile << ' ';
				}
			}
			outputFile << '|' << std::endl;
			workspace.clear();
			incrimentBinnary(values);
		}
	}
	outputFile << std::endl;
}
std::string BooleanExpression::zhegalkin()const {
	if (variables_.size() == 0)
		return infixRecord_;
	else {
		int pow = 1 << variables_.size();
		// получаем коэфициенты в полиноме жегалкина с помощью треугольника Паскаля
		std::vector<bool> leftLine(pow, 0);
		std::vector<bool> result(pow, 0);
		std::vector<bool> values(variables_.size(), 0); //левая(искомая) строка в треугольнике Паскаля, результат, значения переменных
		int maxLen = 0;
		for (int i = 0; i < variables_.size(); ++i) {
			if (maxLen < variables_[i].size())
				maxLen = variables_[i].size();
		}
		std::string polinom((result.size() + 2 + maxLen) * variables_.size() * maxLen, '0');

		// составляем начальную строку коэфициентов в треугольнике
		for (int i = 0; i < pow; ++i) {
			workspace.clear();
			for (int j = 0; j < variables_.size(); ++j)
				workspace.insert(ParamValue(variables_[j], values[j]));
			result[i] = three_->calc();
			incrimentBinnary(values);
		}
		int lenNext = pow - 1;
		std::vector<bool> variable(variables_.size(), 0);
		int j = 0;


		for (int i = 0; i < pow; ++i) {
			leftLine[i] = result[0];// берём самый левый элемент, он будет являтся нужным нам коэфициэнтом, в зависимости от него заполняем строку-результат
			if (leftLine[i]) {
				if (i == 0) {
					polinom[j] = '(';
					++j;
					polinom[j] = '1';
					++j;
					polinom[j] = ')';
					++j;
					polinom[j] = '+';
					++j;
				}
				else {
					polinom[j] = '(';
					++j;
					for (int l = 0; l < variables_.size(); ++l) {
						if (variable[l]) {
							for (int m = 0; m < variables_[l].size(); ++m) {
								polinom[j] = variables_[l][m];
								++j;
							}
							polinom[j] = '&';
							++j;
						}
					}
					if (polinom[j - 1] == '&')
						polinom[j - 1] = ')';
					else {
						polinom[j] = ')';
						++j;
					}
					polinom[j] = '+';
					++j;
				}
			}
			for (int l = 0; l < lenNext; ++l)
				result[l] = result[l] ^ result[l + 1];// вычисляем следующую строку в треугольнике
			--lenNext;//уменьшаем длину строки на 1
			incrimentBinnary(variable);
		}
		while ((polinom[polinom.size() - 1] == '0') || (polinom[polinom.size() - 1] == '+'))
			polinom.pop_back();
		return polinom;
	}
}
bool isFullSystem(const std::vector<BooleanExpression>& system) {
	// проверяем есть ли функции не сохраняющие 0 и 1
	bool saveOne = 0;
	bool saveZero = 0;
	for (int i = 0; i < system.size(); ++i) {
		workspace.clear();
		for (int j = 0; j < system[i].getValue().size(); ++j)
			workspace.insert(ParamValue(system[i].getValue()[j], 1));
		if (system[i].getThree()->calc() == 0)
			saveOne = 1;

		workspace.clear();
		for (int j = 0; j < system[i].getValue().size(); ++j)
			workspace.insert(ParamValue(system[i].getValue()[j], 0));
		if (system[i].getThree()->calc() == 1)
			saveZero = 1;
	}
	if ((!saveOne) || (!saveZero))
		return 0;

	// проверяем есть ли не самодвойственные функции и не монотонные
	bool selfDualGlobal = 0;
	bool monotonusGlobal = 0;
	for (int i = 0; i < system.size(); ++i) {
		std::vector<bool> values(system[i].getValue().size(), 0), resultValues(pow(2, system[i].getValue().size()), 0);
		int pow = 1 << system[i].getValue().size();
		for (int j = 0; j < pow; ++j) {
			workspace.clear();
			for (int l = 0; l < system[i].getValue().size(); ++l)
				workspace.insert(ParamValue(system[i].getValue()[l], values[l]));
			resultValues[j] = system[i].getThree()->calc();
			if (j != pow - 1)
				incrimentBinnary(values);
		}
		if (system[i].getValue().size() == 0) {
			selfDualGlobal = 1;
			continue;
		}
		else {
			for (int m = 0; m < resultValues.size() - 1; ++m) {
				if (resultValues[m] > resultValues[m + 1]) {
					monotonusGlobal = 1;
				}
				if (resultValues[m] == resultValues[resultValues.size() - 1 - m])
					selfDualGlobal = 1;
				if (monotonusGlobal && selfDualGlobal)
					break;
			}
		}
	}
	if ((!selfDualGlobal) || (!monotonusGlobal))
		return 0;

	// проверяем есть ли не линейные функции
	bool linearGlobal = 0;
	for (int i = 0; i < system.size(); ++i) {
		bool linear = 1;
		std::string str = system[i].zhegalkin();
		int countX = 0;
		for (int j = 0; j < str.size(); ++j) {
			if (str[j] == 'x')
				++countX;
			else if (str[j] == '+')
				countX = 0;
			if (countX > 1)
				linearGlobal = 1;
		}
	}
	return (saveZero && saveOne && selfDualGlobal && monotonusGlobal && linearGlobal);
}
