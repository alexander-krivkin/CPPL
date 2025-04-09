#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>


namespace ak
{
	class BigInt final
	{
	public:
		BigInt() {}
		explicit BigInt(const char* str) : data(str) { if (data == "") data = "0"; }
		explicit BigInt(std::string& str) : data(str) { if (data == "") data = "0"; }
		explicit BigInt(const std::string& str) : data(str) { if (data == "") data = "0"; }
		BigInt(const BigInt& other) : data(other.data) {}
		BigInt(BigInt&& other) noexcept { data = other.data; other.data = "0"; }
		~BigInt() {};
		BigInt& operator=(const BigInt& other) { return *this = BigInt(other); }
		BigInt& operator=(BigInt&& other) noexcept { std::swap(data, other.data); return *this; }

		friend std::ostream& operator<<(std::ostream& os, const BigInt& obj);
		std::string getData() const { return data; }
		BigInt operator+(const BigInt& val) const;
		BigInt operator-(const BigInt& val) const;
		BigInt operator*(const BigInt& val) const; // Реализация алгоритма Карацубы

	private:
		std::string data{ "0" };
		BigInt mult10(const BigInt& val, int n) const;
	};
}