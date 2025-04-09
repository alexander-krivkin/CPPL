#include <iostream>
#include <vector>


template <typename T>
void move_vectors(std::vector <T>& one, std::vector <T>& other)
{
	one = std::move(other);
}

int main()
{
	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;
	move_vectors(two, one);

	return EXIT_SUCCESS;
}