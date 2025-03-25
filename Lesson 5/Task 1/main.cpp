#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>


namespace ak
{
	template <typename T>
	T square(const T& arg)
	{
		return arg * arg;
	}

	template <typename T>
	std::vector<T> square(const std::vector<T>& arg)
	{
		std::vector<T> ret{ arg };

		for (auto& elem : ret)
		{
			elem *= elem;
		}

		return ret;
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int i1{ 4 };
	int i2{ 35 };
	double f1{ 22.11 };
	std::vector<int> vec1{ 1, 4, 8, 365 };

	std::cout << "[IN]: " << i1 << std::endl;
	std::cout << "[OUT]: " << ak::square(i1) << std::endl;
	std::cout << "[IN]: " << i2 << std::endl;
	std::cout << "[OUT]: " << ak::square(i2) << std::endl;
	std::cout << "[IN]: " << f1 << std::endl;
	std::cout << "[OUT]: " << ak::square(f1) << std::endl;

	std::cout << "[IN]: ";
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::vector<int> vec1squared{ ak::square(vec1) };

	std::cout << "[OUT]: ";
	std::copy(vec1squared.begin(), vec1squared.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}