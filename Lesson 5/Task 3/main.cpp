#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <Windows.h>


class GetSumFunctor final
{
public:
	GetSumFunctor() : sum(0) {}

	void operator()(int arg)
	{
		if (!(arg % 3)) sum += arg;
	}

	int GetSum() const { return sum; }

private:
	int sum;
};

class GetCountFunctor final
{
public:
	GetCountFunctor() : count(0) {}

	void operator()(int arg)
	{
		if (!(arg % 3)) count++;
	}

	int GetCount() const { return count; }

private:
	int count;
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<int> vec1{ 4, 1, 3, 6, 25, 54, 55, 123, 150, 222 };

	std::cout << "[IN]: ";
	for (auto& elem : vec1)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;

	GetSumFunctor getSumFunctor;
	GetCountFunctor getCountFunctor;

	std::for_each(vec1.begin(), vec1.end(), std::ref(getSumFunctor));
	std::for_each(vec1.begin(), vec1.end(), std::ref(getCountFunctor));

	std::cout << "[OUT]: getSum() = " << getSumFunctor.GetSum() << std::endl;
	std::cout << "[OUT]: getCount() = " << getCountFunctor.GetCount() << std::endl;

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}