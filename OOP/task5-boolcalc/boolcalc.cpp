#include"boolexpr.h"
#include"boolexpr.h"
#include<fstream>
#include<set>

std::set<ParamValue> workspace;// множество переменных
bool isFullSystem(const std::vector<BooleanExpression>& system);

int main(int argc, char* argv[]) {
	if (argc == 4) {
		std::string action = argv[1];
		std::string input = argv[2];
		std::string output = argv[3];
		std::ifstream inputFile(input);
		if (!inputFile.is_open()) {
			std::cout << "Some problems with file";
			return 0;
		}
		std::ofstream outputFile(output);
		if (!outputFile.is_open()) {
			std::cout << "Some problems with file";
			return 0;
		}
		if (action == "-calc") {
			while (!inputFile.eof()) {
				char expression[1024];
				inputFile.getline(expression, 1024);
				BooleanExpression current(expression);
				outputFile << current.calc() << std::endl;
			}
		}
		else if (action == "-cnf") {
			while (!inputFile.eof()) {
				char expression[1024];
				inputFile.getline(expression, 1024);
				BooleanExpression current(expression);
				outputFile << current.cnf() << std::endl;
			}
		}
		else if (action == "-dnf") {
			while (!inputFile.eof()) {
				char expression[1024];
				inputFile.getline(expression, 1024);
				BooleanExpression current(expression);
				outputFile << current.dnf() << std::endl;
			}
		}
		else if (action == "-zh") {
			while (!inputFile.eof()) {
				char expression[1024];
				inputFile.getline(expression, 1024);
				BooleanExpression current(expression);
				outputFile << current.zhegalkin() << std::endl;
			}
		}
		else if (action == "-table") {
			while (!inputFile.eof()) {
				char expression[1024];
				inputFile.getline(expression, 1024);
				BooleanExpression current(expression);
				current.truthTable(outputFile);
			}
		}
		else if (action == "-isfull") {
			std::vector<BooleanExpression> system;
			while (!inputFile.eof()) {
				char expression[1024];
				inputFile.getline(expression, 1024);
				BooleanExpression current(expression);
				system.push_back(current);
			}
			bool resultt = isFullSystem(system);
			if (resultt)
				outputFile << "yes";
			else
				outputFile << "no";
		}
		inputFile.close();
		outputFile.close();
	}
	else if (argc == 2) {
		std::string str = argv[1];
		if ((str == "-h") || (str == "?")) {
			setlocale(LC_ALL, "Russian");
			std::cout << "Вызов boolcalc -calc input output осуществляет вычисление выражений записанных в файле input (значения переменных запрашивает у пользователя) и записывает результаты в файл output (для каждой функции результат записывается в отдельной строке)" << std::endl << std::endl;
			std::cout << "Вызов boolcalc -cnf input output осуществляет построение конъюнктивной нормальной формы для выражений записанных в файле input и записывает результаты в файл output (для каждой функции результат записывается в отдельной строке)." << std::endl << std::endl;
			std::cout << "Вызов boolcalc -dnf input output осуществляет построение дизъюнктивной нормальной формы для выражений записанных в файле input и записывает результаты в файл output (для каждой функции результат записывается в отдельной строке)." << std::endl << std::endl;
			std::cout << "Вызов boolcalc -zh input output осуществляет построение полинома Жегалкина для выражений записанных в файле input и записывает результаты в файл output (для каждой функции результат записывается в отдельной строке)." << std::endl << std::endl;
			std::cout << "Вызов boolcalc -table input выводит в консоль таблицу истинности для всех выражений записанных в файле input." << std::endl << std::endl;
			std::cout << "Вызов boolcalc -isfull input output проверяет систему функций на полноту. Если система функций в файле input полная, то в файл output выводится yes, иначе no" << std::endl << std::endl;
			std::cout << "Вызов boolcalc -h или boolcalc ? выводит на экран помощь по использованию программы." << std::endl << std::endl;
		}
		else {
			setlocale(LC_ALL, "Russian");
			std::cout << "Введена неизвестная команда, ознакомтесь с инструкцие работы с программой и попробуйте ещё раз" << std::endl;
		}
	}
	else {
		setlocale(LC_ALL, "Russian");
		std::cout << "Введена неизвестная команда, ознакомтесь с инструкцие работы с программой и попробуйте ещё раз" << std::endl;
	}
}
