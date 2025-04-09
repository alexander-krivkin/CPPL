#include "BigInt.h"

int main()
{
	try
	{
		auto number1 = ak::BigInt("114575");
		auto number2 = ak::BigInt("78524");
		auto result = number1 * number2;

		auto number3 = std::move(result);
		std::cout << number3 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception thrown: " << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << std::endl;
	return EXIT_SUCCESS;
}