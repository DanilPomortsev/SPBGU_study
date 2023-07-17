#include<iostream>
#include<fstream>
#include"turingmachine.h"

int main(int argc, char* argv[]) {
	TuringMachine m(argv[1], argv[2]);
	std::string result;
	std::ofstream outfile(argv[3]);
	if (!outfile.is_open()) {
		std::cout << "Problems with file, try one more time";
		return 0;
	}
	if (m.getError() == 1) //проверка на ошибку
		outfile << "Error";
	else {
		result = m.calc(m.getFirstCondition(), m.getNumberOfTakt()); //вычисляем ленту
		if (m.getAplicate() == 1)//проверка на количество тактов
			outfile << "Not applicable";
		else {
			for (int i = 0; i < result.length(); ++i)//вывод ленты с финальной позиции
				outfile << result[i];
		}
	}
	outfile.close();
}
