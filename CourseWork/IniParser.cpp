#include "IniParser.h"


namespace ak
{
	std::vector<std::string> syntaxName{ "ok: init section", "ok: init variable",
		"Error: invalid name", "Error: no defifnition", "Error: unexpected symbols" };

	bool isLetterDigit(const char& ch) {
		return (((ch >= 'A') && (ch <= 'Z')) ||
			((ch >= 'a') && (ch <= 'z')) || ((ch >= '1') && (ch <= '9')));
	}
	bool isDigit(const char& ch) { return ((ch >= '0') && (ch <= '9')); }
	bool isDigitDot(const char& ch) { return (((ch >= '0') && (ch <= '9')) || (ch == '.')); }

	IniParser::IniParser(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file)
		{
			throw(std::exception("ошибка открыти€ файла"));
		}

		std::string line{};
		while (std::getline(file, line))
		{
			rawLines_.emplace_back(line);
		}

		cleanRawLines();
		printLines();
		std::cout << std::endl;
		parseData();
		printSyntax();
		std::cout << std::endl;
		printContainer();
		std::cout << std::endl;
	}

	void IniParser::printRawLines() const
	{
		int idx{};
		for (const auto& elem : rawLines_)
		{
			std::cout << std::setw(3) << ++idx << ": " << '\"' << elem << '\"' << std::endl;
		}
	}

	void IniParser::printLines() const
	{
		int idx{};
		for (const auto& elem : lines_)
		{
			std::cout << std::setw(3) << ++idx << ": " << '\"' << elem << '\"' << std::endl;
		}
	}

	void IniParser::printSyntax() const
	{
		int idx{};
		for (const auto& elem : syntax_)
		{
			std::cout << std::setw(3) << ++idx << ": " << syntaxName[static_cast<int>(elem)] << std::endl;
		}
	}

	void IniParser::printContainer() const
	{
		for (const auto& key : container_)
		{
			std::cout << "[" << key.first << "]" << std::endl;
			for (const auto& elem : key.second)
			{
				std::cout << "    " << elem.first << " = " << elem.second << std::endl;
			}
		}
	}

	void IniParser::cleanRawLines()
	{
		// 1. ”даление комментариев
		for (const auto& elem : rawLines_)
		{
			auto it = std::find(elem.begin(), elem.end(), ';');
			lines_.emplace_back(std::string(elem.begin(), it));
		}

		// 2. ”даление пробелов и символов табул€ции до знаков [
		for (auto& elem : lines_)
		{
			auto it = std::find(elem.begin(), elem.end(), '[');
			if (it != elem.end())
			{
				elem.erase(std::remove_if(elem.begin(), it,
					[](char ch) { return ((ch == ' ') || (ch == '\t')); }),
					it);
			}
		}

		// 3. ”даление пробелов и символов табул€ции после знаков ]
		for (auto& elem : lines_)
		{
			auto it = std::find(elem.begin(), elem.end(), ']');
			if (it != elem.end())
			{
				elem.erase(std::remove_if(it, elem.end(),
					[](char ch) { return ((ch == ' ') || (ch == '\t')); }),
					elem.end());
			}
		}

		// 4. ”даление пробелов и символов табул€ции до знаков =
		for (auto& elem : lines_)
		{
			auto it = std::find(elem.begin(), elem.end(), '=');
			if (it != elem.end())
			{
				elem.erase(std::remove_if(elem.begin(), it,
					[](char ch) { return ((ch == ' ') || (ch == '\t')); }),
					it);
			}
		}

		// 5. ”даление завершающих строки пробелов и символов табул€ции (кодова€ страница 1251)
		for (auto& elem : lines_)
		{
			elem.erase(std::find_if(elem.rbegin(), elem.rend(),
				[](char ch) { return ((ch != ' ') && (ch != '\t')); }).base(),
				elem.end());
		}

		// 6. ”даление пустых строк
		std::erase(lines_, "");
	}

	void IniParser::parseData()
	{
		std::string currentSection{ "Empty" };
		std::string currentVariable{};
		std::string currentVariableValue{};
		
		syntax_.resize(lines_.size());
		std::fill(syntax_.begin(), syntax_.end(), Syntax::eErrNoDefinition);
		int syntaxIdx{};

		for (const auto& elem : lines_)
		{
			// —екции
			auto lines_it = std::find(elem.begin(), elem.end(), '[');
			auto lines_it_end = std::find(lines_it, elem.end(), ']');
			if ((lines_it != elem.end()) && (lines_it_end != elem.end()))
			{
				if (std::find_if_not(lines_it + 1, lines_it_end, isLetterDigit) == lines_it_end)
				{
					syntax_[syntaxIdx] = Syntax::eInitSection;
					currentSection = std::string(lines_it + 1, lines_it_end);

					if (!container_[currentSection].size())
					{
						container_[currentSection].clear();
					}
				}
				else
				{
					syntax_[syntaxIdx] = Syntax::eErrInvalidName;
				}
			}

			// ѕеременные
			lines_it = std::find(elem.begin(), elem.end(), '=');
			if (lines_it != elem.end())
			{
				if (std::find_if_not(elem.begin(), lines_it, isLetterDigit) == lines_it)
				{
					currentVariable = std::string(elem.begin(), lines_it);
				}
				else
				{
					syntax_[syntaxIdx] = Syntax::eErrInvalidName;
				}

				currentVariableValue = std::string(lines_it + 1, elem.end());
				if (currentVariableValue.length())
				{
					syntax_[syntaxIdx] = Syntax::eInitVariable;
					container_[currentSection][currentVariable] = currentVariableValue;
				}
				else
				{
					syntax_[syntaxIdx] = Syntax::eErrNoDefinition;
				}
			}

			syntaxIdx++;
		}
	}
}