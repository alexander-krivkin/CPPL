#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <Windows.h>


bool comp(std::pair<char, int>& a, std::pair<char, int>& b) {
	return a.second > b.second;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int num{};

	std::cout << "[IN]: " << std::endl;
	std::cin >> num;
	std::vector<int> v1{};
	std::set <int, std::greater<int>> s1{};
	v1.resize(num);

	for (size_t idx{}; idx < num; idx++)
	{
		std::cin >> v1.at(idx);
		s1.emplace(v1.at(idx));
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