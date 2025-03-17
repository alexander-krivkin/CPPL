#include <iostream>
#include <string>
#include <Windows.h>

#include "SmartArray.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		ak::SmartArray arr(3);
		ak::SmartArray new_array(2);

		arr.addElement(1);
		arr.addElement(4);
		arr.addElement(155);
		arr.addElement(14);
		arr.addElement(15);
		arr.print();

		new_array.addElement(44);
		new_array.addElement(34);
		new_array.print();

		arr = new_array;
		arr.print();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception: " << ex.what() << std::endl;
	}

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}