#include "MainNeuro.h"

using namespace std;

void randfill_array(double* arr, size_t size) {
	for (size_t i = 0; i < size; i++)
		arr[i] = ((rand() % 1001) - 500) / 100.0;
}

void show_array(double* arr, size_t size) {
	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << "\t";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	// формируем обучающую выборку 
	std::cout << "Введите количество генерируемых точек: ";
	unsigned int point_quantity;
	std::cin >> point_quantity;

	double* x = new double[point_quantity];
	double* y = new double[point_quantity];
	
	randfill_array(x, point_quantity);
	randfill_array(y, point_quantity);

	std::cout << "\nЗначения x:\t";
	show_array(x, point_quantity);
	std::cout << "\nЗначения y:\t";
	show_array(y, point_quantity);
	
	// обучаем сеть
	DeltaPerceptron DeltaPer(50000, 0.001);

	DeltaPer.fit(x, y, point_quantity);

	//восвобождаем лишнюю память
	delete[] x;
	delete[] y;

	// получаем результаты из сети
	std::cout << "\n";
	DeltaPer.show_params();
	std::cout << "\n";
}
