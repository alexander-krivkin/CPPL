#include <iostream>
#include <Windows.h>

#include "Vector.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		ak::Vector<float> v1;

		std::cout << "capacity: " << v1.getCapacity() << "  size: " << v1.getSize() << std::endl;
		std::cout << v1 << std::endl << std::endl;

		v1.PushBack(11.1f);
		v1.PushBack(21.1f);
		v1.PushBack(22.2f);
		std::cout << "capacity: " << v1.getCapacity() << "  size: " << v1.getSize() << std::endl;
		std::cout << v1 << std::endl << std::endl;

		v1.PushBack(33);
		v1.PushBack(43);
		std::cout << "capacity: " << v1.getCapacity() << "  size: " << v1.getSize() << std::endl;
		std::cout << v1 << std::endl << std::endl;

		v1.PushBack(44);
		std::cout << "capacity: " << v1.getCapacity() << "  size: " << v1.getSize() << std::endl;
		std::cout << v1 << std::endl << std::endl;

		std::cout << "v[1]= " << v1.getElemAt(1) << std::endl;
		std::cout << "v[3]= " << v1.getElemAt(3) << std::endl;
		std::cout << "v[21]= " << v1.getElemAt(21) << std::endl;
		std::cout << "v[5]= " << v1.getElemAt(5) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception: " << ex.what() << ". Execution aborted" << std::endl;

		std::cout << std::endl << std::endl;
		system("pause");
		return EXIT_FAILURE;

	}

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}