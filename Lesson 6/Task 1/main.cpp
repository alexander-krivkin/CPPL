#include <iostream>
#include <string>
#include <vector>
#include <map>
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

	std::string str1{ "Hello World!!" };
	std::multiset<char> ms1{};
	std::map<char, int> mm1{};
	std::vector<std::pair<char, int>> v1{};

	std::cout << "[IN]: " << str1 << std::endl;

	for (auto& elem : str1)
	{
		ms1.emplace(elem);
	}

	for (auto& elem : ms1)
	{
		mm1.insert({ elem, ms1.count(elem) });
	}

	v1 = std::vector<std::pair<char, int>>{ mm1.begin(), mm1.end()};
	std::sort(v1.begin(), v1.end(), comp);

	std::cout << "[OUT]: " << std::endl;
	for (auto& elem : v1)
	{
		std::cout << elem.first << ": " << elem.second << std::endl;
	}

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}