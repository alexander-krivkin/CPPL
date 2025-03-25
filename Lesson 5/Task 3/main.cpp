#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <Windows.h>


class CounterFunctor final
{
public:
	CounterFunctor() : sum(0), count(0) {}

	void operator()(int arg)
	{
		if (!(arg % 3))
		{
			sum += arg;
			count++;
		}
	}

	int GetSum() const { return sum; }
	int GetCount() const { return count; }

private:
	int sum;
	int count;
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<int> vec1{ 4, 1, 3, 6, 25, 54, 55, 123, 150, 222 };

	std::cout << "[IN]: ";
	std::copy(vec1.begin(), vec1.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	CounterFunctor counter = std::for_each(vec1.begin(), vec1.end(), CounterFunctor());

	std::cout << "[OUT]: getSum() = " << counter.GetSum() << std::endl;
	std::cout << "[OUT]: getCount() = " << counter.GetCount() << std::endl;

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}