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
	enum class Syntax
	{
		eInitSection = 0,
		eInitVariable = 1,
		eErrInvalidName = 2,
		eErrNoDefinition = 3,
		eErrUnexpectedSymbols = 4
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
			static_assert(sizeof(T) == -1, "not implemented type for getValue");
		}

		template <>
		int getValue(std::string query)
		{
			return std::atoi(getStringValue_(query).data());
		}

		template <>
		float getValue(std::string query)
		{
			return static_cast<float>(std::atof(getStringValue_(query).data()));
		}

		template <>
		double getValue(std::string query)
		{
			return std::atof(getStringValue_(query).data());
		}

		template <>
		std::string getValue(std::string query)
		{
			return getStringValue_(query);
		}

	private:
		void printRawLines() const;
		void printLines() const;
		void printSyntax() const;
		void printContainer() const;
		void cleanRawLines();
		void parseData();

		std::string getStringValue_(std::string query)
		{
			auto it = std::find(query.begin(), query.end(), '.');
			std::string section(query.begin(), it);
			std::string variable(it + 1, query.end());

			return container_[section][variable];
		}

		std::vector<std::string> rawLines_{};
		std::vector<std::string> lines_{};
		std::vector <Syntax> syntax_{};
		std::map<std::string, std::map<std::string, std::string>> container_{};
	};
}