#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <variant>


namespace ak
{
	enum class SyntaxType
	{
		ERR = 0,
		INIT_SECTION = 1,
		INIT_INT = 2,
		INIT_DOUBLE = 3,
		INIT_STRING = 4,
		INIT_UNDEFINED = 5
	};
	enum class SyntaxStatus
	{
		OK = 0,
		ERR_INVALID_NAME = 1,
		ERR_NO_DEFINITION = 2,
		ERR_UNEXPECTED_SYMBOLS = 3,

		ERR_INVALID_NAME_AND_NO_DEFINITION = 11,
		ERR_INVALID_NAME_AND_UNEXPECTED_SYMBOLS = 12,
		ERR_TYPE_CHANGED_AND_UNEXPECTED_SYMBOLS = 13
	};

	bool isLetterDigit(const char& ch);
	bool isDigit(const char& ch);
	bool isDigitDot(const char& ch);

	class IniParser final
	{
	public:
		IniParser() = delete;
		explicit IniParser(const std::string& filename);
		~IniParser() {};
		IniParser& operator=(const IniParser& other) = delete;

		template <typename T>
		T getValue(std::string query)
		{
			auto it = std::find(query.begin(), query.end(), '.');
			std::string section(query.begin(), it);
			std::string variable(it + 1, query.end());

			return std::get<T>(container_[section][variable]);
		}

	private:
		void printRawLines() const;
		void printLines() const;
		void printSyntax() const;
		void printContainer() const;
		void cleanRawLines();
		void parseData();

		std::vector<std::string> rawLines_{};
		std::vector<std::string> lines_{};
		std::vector <std::pair<SyntaxType, SyntaxStatus>> syntax_{};

		typedef std::map<std::string, std::variant<int, double, std::string>> tMapVariants;
		std::map<std::string, tMapVariants> container_{};
	};
}