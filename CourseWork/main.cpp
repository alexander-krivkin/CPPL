#include "IniParser.h"

#include <windows.h>


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		ak::IniParser iniParser("file.ini");

		std::string query{ "Section1.var1" };
		auto value = iniParser.getValue<double>(query);
		std::cout << query << ": value = " << value;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Исключение: " << ex.what() << std::endl << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}