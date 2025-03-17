#include "SmartArray.h"


ak::SmartArray::SmartArray(int size) :
	physicalSize(size), logicalSize(0)
{
	data = new int[physicalSize] {};
}

ak::SmartArray::~SmartArray()	
{
	physicalSize = 0;
	logicalSize = -1;
	delete[] data;
}

ak::SmartArray& ak::SmartArray::operator=(const ak::SmartArray& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	physicalSize = rhs.physicalSize;
	logicalSize = rhs.logicalSize;
	delete[] data;

	data = new int[physicalSize] {};

	for (int idx{}; idx < logicalSize; idx++)
	{
		data[idx] = rhs.data[idx];
	}
}


void ak::SmartArray::print() const
{
	for (int idx{}; idx < logicalSize; idx++)
	{
		std::cout << data[idx] << " ";
	}
	std::cout << std::endl;
}

void ak::SmartArray::addElement(int elem)
{
	if (physicalSize > logicalSize)
	{
		data[logicalSize] = elem;
		logicalSize++;
	}
	else
	{
		int tmpPhysicalSize = 2 * physicalSize;
		int* tmpData = new int[tmpPhysicalSize] {};

		for (int idx{}; idx < logicalSize; idx++)
		{
			tmpData[idx] = data[idx];
		}
		if (tmpPhysicalSize > logicalSize)
		{
			tmpData[logicalSize] = elem;
		}

		physicalSize = tmpPhysicalSize;
		logicalSize++;
		delete[] data;
		data = new int[physicalSize] {};

		for (int idx{}; idx < logicalSize; idx++)
		{
			data[idx] = tmpData[idx];
		}

		delete[] tmpData;
	}
}

int ak::SmartArray::getElement(int index) const
{
	if ((index < 0) || (index >= logicalSize))
	{
		throw std::exception("out of range");
	}

	return data[index];
}
