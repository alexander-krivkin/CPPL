#include "IniParser.h"


namespace ak
{
	std::vector<std::string> syntaxTypeName { "ERR", "INIT_SECTION", "INIT_INT", "INIT_DOUBLE", "INIT_STRING", "INIT_UNDEFINED" };
	std::vector<std::string> syntaxStatusName{ "", " - ERR_INVALID_NAME", " - ERR_NO_DEFINITION", " - ERR_UNEXPECTED_SYMBOLS" };

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
			std::cout << std::setw(3) << ++idx << ": " <<
				syntaxTypeName[static_cast<int>(elem.first)] <<
				syntaxStatusName[static_cast<int>(elem.second)] << std::endl;
		}
	}

	void IniParser::printContainer() const
	{
		for (const auto& key : container_)
		{
			std::cout << "[" << key.first << "]" << std::endl;

			for (const auto& elem : key.second)
			{
				std::cout << '\t' << elem.first;
				switch (elem.second.index())
				{
				case 0:
					std::cout << " (int) = " <<
						std::get<int>(elem.second) << std::endl;
					break;
				case 1:
					std::cout << " (double) = " <<
						std::get<double>(elem.second) << std::endl;
					break;
				case 2:
					std::cout << " (string) = " <<
						std::get<std::string>(elem.second) << std::endl;
					break;
				default:
					break;
				}
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
		syntax_.resize(lines_.size());
		auto syntax_it = syntax_.begin();
		std::string currentSection{ "Empty" };
		std::string currentVariable{};
		std::string currentVariableValue{};

		for (const auto& elem : lines_)
		{
			// l - заглавные и прописные символы латинского алфавита и цифры
			// n - цифры
			// x - любые символы

			// 1. ѕроверка синтаксиса "[l]"
			auto lines_it = std::find(elem.begin(), elem.end(), '[');
			auto lines_it_end = std::find(lines_it, elem.end(), ']');
			if ((lines_it != elem.end()) && (lines_it_end != elem.end()))
			{
				syntax_it->first = SyntaxType::INIT_SECTION;

				if (std::find_if_not(lines_it + 1, lines_it_end, isLetterDigit) == lines_it_end)
				{
					syntax_it->second = SyntaxStatus::OK;					
					currentSection = std::string(lines_it + 1, lines_it_end);

					if (!container_[currentSection].size())
					{
						container_[currentSection].clear();
					}
				}
				else
				{
					syntax_it->second = SyntaxStatus::ERR_INVALID_NAME;
				}
			}

			// 2. ѕроверка синтаксисов "l=n" "l=n.n" "l=x"
			lines_it = std::find(elem.begin(), elem.end(), '=');
			if (lines_it != elem.end())
			{
				if (std::find_if_not(elem.begin(), lines_it, isLetterDigit) == lines_it)
				{
					currentVariable = std::string(elem.begin(), lines_it);
				}
				else
				{
					syntax_it->second = SyntaxStatus::ERR_INVALID_NAME;
				}

				currentVariableValue = std::string(lines_it + 1, elem.end());
				if (!currentVariableValue.length())
				{
					syntax_it->first = SyntaxType::INIT_UNDEFINED;
					syntax_it->second = SyntaxStatus::ERR_NO_DEFINITION;
				}
				else if (std::find_if_not(currentVariableValue.begin(), currentVariableValue.end(), isDigit) ==
					currentVariableValue.end())
				{
					syntax_it->first = SyntaxType::INIT_INT;
					syntax_it->second = SyntaxStatus::OK;
					int val = std::stoi(currentVariableValue);
					container_[currentSection][currentVariable] = val;
				}
				else if (std::find_if_not(currentVariableValue.begin(), currentVariableValue.end(), isDigitDot) ==
					currentVariableValue.end())
				{
					syntax_it->first = SyntaxType::INIT_DOUBLE;
					syntax_it->second = SyntaxStatus::OK;
					double val = std::stod(currentVariableValue);
					container_[currentSection][currentVariable] = val;
				}
				else
				{
					syntax_it->first = SyntaxType::INIT_STRING;
					syntax_it->second = SyntaxStatus::OK;
					container_[currentSection][currentVariable] = currentVariableValue;
				}
			}

			// 3. Ћюбой другой вариант - ошибка синтаксиса

			syntax_it++;
		}
	}
}