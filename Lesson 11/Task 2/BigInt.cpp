#include "BigInt.h"

namespace ak
{
	int multTable[10][10]
	{
		{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
		{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9 },
		{ 0,  2,  4,  6,  8, 10, 12, 14, 16, 18 },
		{ 0,  3,  6,  9, 12, 15, 18, 21, 24, 27 },
		{ 0,  4,  8, 12, 16, 20, 24, 28, 32, 36 },
		{ 0,  5, 10, 15, 20, 25, 30, 35, 40, 45 },
		{ 0,  6, 12, 18, 24, 30, 36, 42, 48, 54 },
		{ 0,  7, 14, 21, 28, 35, 42, 49, 56, 63 },
		{ 0,  8, 16, 24, 32, 40, 48, 56, 64, 72 },
		{ 0,  9, 18, 27, 36, 45, 54, 63, 72, 81 }
	};

	BigInt BigInt::operator+(const BigInt& val) const
	{
		int n = static_cast<int>(max(data.length(), val.data.length()));

		std::string ret(n + 1, '0');
		ret.replace(n + 1 - data.length(), data.length(), data);

		int a{}, b{}, c{};
		int add10{ 0 };
		char ch;
		auto it_ret = ret.end();
		auto it_val = val.data.end();

		do
		{
			// TODO если символ не цифра, то выброс исключения
			it_ret--;
			a = static_cast<int>(*it_ret) - static_cast<int>('0');

			if (it_val != val.data.begin())
			{
				it_val--;
				b = static_cast<int>(*it_val) - static_cast<int>('0');
			}
			else { b = 0; }

			c = a + b + add10;
			if (c >= 10)
			{
				c -= 10;
				add10 = 1;
			}
			else { add10 = 0; }

			ch = static_cast<char>(c) + static_cast<char>('0');
			ret.replace(it_ret, next(it_ret), 1, ch);
		} while (it_ret != ret.begin());

		ret.erase(0, ret.find_first_not_of('0'));
		if (ret.empty()) { ret.append(1, '0'); }

		BigInt bigIntRet(ret);
		return bigIntRet;
	}

	BigInt BigInt::operator-(const BigInt& val) const
	{
		int n = static_cast<int>(max(data.length(), val.data.length()));

		std::string ret(n, '0');
		ret.replace(n - data.length(), data.length(), data);

		int a{}, b{}, c{};
		int sub10{ 0 };
		char ch;
		auto it_ret = ret.end();
		auto it_val = val.data.end();

		do
		{
			// TODO если символ не цифра, то выброс исключения
			it_ret--;
			a = static_cast<int>(*it_ret) - static_cast<int>('0');

			if (it_val != val.data.begin())
			{
				it_val--;
				b = static_cast<int>(*it_val) - static_cast<int>('0');
			}
			else { b = 0; }

			c = a - b - sub10;
			if (c < 0)
			{
				c += 10;
				sub10 = 1;
			}
			else { sub10 = 0; }

			ch = static_cast<char>(c) + static_cast<char>('0');
			ret.replace(it_ret, next(it_ret), 1, ch);

		} while (it_ret != ret.begin());

		ret.erase(0, ret.find_first_not_of('0'));
		if (ret.empty()) { ret.append(1, '0'); }

		BigInt bigIntRet(ret);
		return bigIntRet;
	}

	BigInt BigInt::operator*(const BigInt& val) const
	{
		int n_this = data.length();
		int n_val = val.data.length();

		if ((n_this == 1) && (n_val == 1))
		{
			int ret = (multTable[std::stoi(data)][std::stoi(val.data)]);

			BigInt bigIntRet(std::to_string(ret));
			return bigIntRet;
		}

		int max_log2 = static_cast<int>(max(ceil(log2(data.length())), ceil(log2(val.data.length()))));
		int n = pow(2, max_log2);
		int n_2 = n / 2;

		std::string x(n - n_this, '0');
		std::string y(n - n_val, '0');
		x.append(data);
		y.append(val.data);

		BigInt a(x.substr(0, n / 2));
		BigInt b(x.substr(n / 2, n / 2));
		BigInt c(y.substr(0, n / 2));
		BigInt d(y.substr(n / 2, n / 2));

		auto ac = a * c;
		auto bd = b * d;
		auto p = a + b;
		auto q = c + d;
		auto pq = p * q;
		auto ad_bc = (pq - ac) - bd;

		BigInt ret = mult10(ac, n) + mult10(ad_bc, n_2) + bd;
		return ret;
	}

	BigInt BigInt::mult10(const BigInt& val, int n) const
	{
		BigInt ret(val);
		ret.data.append(n, '0');
		return ret;
	}


	std::ostream& operator<<(std::ostream& os, const BigInt& obj)
	{
		os << obj.getData();
		return os;
	}
}