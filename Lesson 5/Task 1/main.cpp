#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>


template <typename T1>
void squareAndPrint(T1 arg)
{
	std::cout << "[IN]: " << arg << std::endl;
	std::cout << "[OUT]: " << arg * arg << std::endl;
}

template <typename T2>
void squareAndPrint(std::vector<T2> arg)
{
	std::cout << "[IN]: ";
	for (auto& elem : arg)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	std::cout << "[OUT]: ";
	for (auto& elem : arg)
	{
		std::cout << elem * elem << " ";
	}
	std::cout << std::endl;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int i1{ 4 };
	int i2{ 35 };
	double f1{ 22.11 };
	std::vector<int> vec1{ 1, 4, 8, 365 };
	std::vector<float> vec2{ 1.1, 4.2, 8.3, 365.4 };

	squareAndPrint(i1);
	squareAndPrint(i2);
	squareAndPrint(f1);
	squareAndPrint(vec1);
	squareAndPrint(vec2);

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}