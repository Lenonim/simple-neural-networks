#include <iostream>
#include "LogicNetwork.h"

int main()
{	
	setlocale(LC_ALL, "RUSSIAN");

	std::cout << "Таблицы истинности\n";

	std::cout << "\nИмпликация\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "x = " << points_data[i][0] << " y = " << points_data[i][1]
			<< " answ = " << IMP(points_data[i][0], points_data[i][1]) <<"\n";
	}

	std::cout << "\nСтрелка Шеффера\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "x = " << points_data[i][0] << " y = " << points_data[i][1]
			<< " answ = " << SHEFFER(points_data[i][0], points_data[i][1]) << "\n";
	}

	std::cout << "\nЛогическое ИЛИ\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "x = " << points_data[i][0] << " y = " << points_data[i][1]
			<< " answ = " << OR(points_data[i][0], points_data[i][1]) << "\n";
	}

	std::cout << "\nИсключающее ИЛИ\n";
	for (int i = 0; i < 4; i++) {
		std::cout << "x = " << points_data[i][0] << " y = " << points_data[i][1]
			<< " answ = " << XOR(points_data[i][0], points_data[i][1]) << "\n";
	}

	std::cout << "\nPIRS( x, AND( y, z ))\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				std::cout << "x = " << points_data[1][i] << " y = " << points_data[1][j] << " z = " << points_data[1][k]
					<< " answ = " << PIRS(points_data[1][i], AND(points_data[1][j], points_data[1][k])) << "\n";
			}
		}
	}

	std::cout << "\nСложные выражения\n";

	std::cout << "\nSHEFFER( NRIMP(true, true), OR(false, true)) = " << SHEFFER(NRIMP(true, true), OR(false, true)) << "\n";

	std::cout << "\nRIMP( NOT( EQ( true, true ) ), AND( false, XOR ( true, false ))) = " << RIMP(NOT( XOR(true, true)), AND(false, XOR(true, false))) << "\n";
}

