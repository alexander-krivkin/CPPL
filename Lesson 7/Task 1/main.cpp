#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <Windows.h>


namespace ak
{
	template <typename T>
	void printContainer(const std::set<T>& obj)
	{
		for_each(obj.begin(), obj.end(), [](T el) { std::cout << el << " "; });
	}

	template <typename T>
	void printContainer(const std::list<T>& obj)
	{
		for_each(obj.begin(), obj.end(), [](T el) { std::cout << el << " "; });
	}

	template <typename T>
	void printContainer(const std::vector<T>& obj)
	{
		for_each(obj.begin(), obj.end(), [](T el) { std::cout << el << " "; });
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::set<std::string> testSet { "one", "two", "three", "four" };
	ak::printContainer(testSet);
	std::cout << std::endl;

	std::list<std::string> testList{ "one", "two", "three", "four" };
	ak::printContainer(testList);
	std::cout << std::endl;

	std::vector<std::string> testVector{ "one", "two", "three", "four" };
	ak::printContainer(testVector);

	std::cout << std::endl << std::endl;
	return EXIT_SUCCESS;
}