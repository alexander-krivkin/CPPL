#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>


namespace ak
{
	template <typename T>
	std::vector<T> eraseDuplicates(const std::vector<T>& obj)
	{
		std::vector<T> ret{ obj };
		sort(ret.begin(), ret.end());
		auto it = unique(ret.begin(), ret.end());
		ret.erase(it, ret.end());

		return ret;
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<int> v1{ 1, 2, 5, 3, 7, 5, 1, 3, 2, 9, 5, 1, 4, 5, 2 };
	auto v2 = ak::eraseDuplicates(v1);

	for_each(v1.begin(), v1.end(), [](int el) { std::cout << el << " "; });
	std::cout << std::endl;
	for_each(v2.begin(), v2.end(), [](int el) { std::cout << el << " "; });

	std::cout << std::endl << std::endl;
	return EXIT_SUCCESS;
}