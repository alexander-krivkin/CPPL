#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <Windows.h>


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int num{};

	std::cout << "[IN]: " << std::endl;
	std::cin >> num;
	std::set <int, std::greater<int>> s1{};

	for (size_t idx{}; idx < num; idx++)
	{
		int n{};
		std::cin >> n;
		s1.insert(n);
	}

	std::cout << std::endl << "[OUT]: " << std::endl;

	for (auto& elem : s1)
	{
		std::cout << elem << std::endl;
	}

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}