#ifndef AK_SMART_ARRAY_H
#define AK_SMART_ARRAY_H

#include <iostream>


namespace ak
{
	class SmartArray final
	{
	public:
		SmartArray(int size);
		~SmartArray();

		int getPhysicalSize() const { return physicalSize; }
		int getLogicalSize() const { return logicalSize; }

		void print() const;
		void addElement(int elem);
		int getElement(int index) const;

	private:
		int* data;
		int physicalSize;
		int logicalSize;
	};
}

#endif