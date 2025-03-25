#include <string>
#include <iostream>
#include <Windows.h>

#include "List.h"
#include "test_list.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	return Catch::Session().run();;
}