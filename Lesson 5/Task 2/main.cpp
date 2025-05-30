#include <iostream>
#include <string>
#include <Windows.h>


template <typename T>
class Table final
{
public:
	Table(int sizeX, int sizeY) : sizeX(sizeX), sizeY(sizeY)
	{
		data = new T*[sizeX]{};

		for (int idxX{}; idxX < sizeX; idxX++)
		{
			data[idxX] = new T[sizeY]{};
		}
	}

	Table(const Table& obj)
	{
		sizeX = obj.sizeX;
		sizeY = obj.sizeY;

		data = new T * [sizeX] {};

		for (int idxX{}; idxX < sizeX; idxX++)
		{
			data[idxX] = new T[sizeY]{};

			for (int idxY{}; idxY < sizeY; idxY++)
			{
				data[idxX][idxY] = obj.data[idxX][idxY];
			}
		}
	}

	Table& operator=(const Table& obj)
	{
		if (this == &obj)
		{
			return *this;
		}

		for (int idxX{}; idxX < sizeX; idxX++)
		{
			delete[] data[idxX];
		}

		delete[] data;

		sizeX = obj.sizeX;
		sizeY = obj.sizeY;

		data = new T * [sizeX] {};

		for (int idxX{}; idxX < sizeX; idxX++)
		{
			data[idxX] = new T[sizeY]{};

			for (int idxY{}; idxY < sizeY; idxY++)
			{
				data[idxX][idxY] = obj.data[idxX][idxY];
			}
		}
	}

	virtual ~Table()
	{
		for (int idxX{}; idxX < sizeX; idxX++)
		{
			delete[] data[idxX];
		}

		delete[] data;
	}

	void PrintSize() const
	{
		std::cout << "Table size: " << sizeX << " x " << sizeY << std::endl;
	}
		
	void Print() const
	{
		for (int idxY{}; idxY < sizeY; idxY++)
		{
			for (int idxX{}; idxX < sizeX; idxX++)
			{
				std::cout << data[idxX][idxY] << " ";
			}
			std::cout << std::endl;
		}
	}


	class Proxy
	{
	public:
		Proxy(T* data) : data(data) {}
		const T& operator[] (int idx) const
		{
			return data[idx];
		}
		T& operator[] (int idx)
		{
			return data[idx];
		}
	private:
		T* data;
	};

	const Proxy& operator[](int idx) const 
	{
		return Proxy(data[idx]);
	}

	Proxy operator[](int idx)
	{
		return Proxy(data[idx]);
	}

private:
	int sizeX, sizeY;
	T** data;
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	auto table = Table<double>(7, 3);
	table.PrintSize();
	table.Print();
	table[3][1] = 22.11;
	std::cout << "Table[3][1] = " << table[3][1] << std::endl;
	table.Print();

	std::cout << std::endl << std::endl;
	system("pause");
	return EXIT_SUCCESS;
}