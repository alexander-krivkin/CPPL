#ifndef AK_VECTOR_H
#define AK_VECTOR_H

#include <iostream>


namespace ak
{
	template <typename T>
	class Vector final
	{
	public:
		Vector() : capacity(5), size(0)
		{ data = new T[capacity]{};	}
		Vector(const Vector& obj) : capacity(obj.capacity), size(obj.size)
		{
			data = new T[capacity]{};
			for (size_t idx{}; idx < size; idx++)
			{
				data[idx] = obj.data[idx];
			}
		}
		virtual ~Vector() {	delete[] data; }

		Vector& operator= (const Vector& obj)
		{
			if (this == &obj) { return *this; }

			delete[] data;

			data = new T[capacity]{};
			for (size_t idx{}; idx < size; idx++)
			{
				data[idx] = obj.data[idx];
			}

			return *this;
		}

		//friend std::ostream& operator<< (std::ostream& stream, const Vector<T>& obj);

		size_t getCapacity() const { return capacity; }
		size_t getSize() const { return size; }
		T getElemAt(size_t idx) const
		{
			if (idx > size) { throw std::exception("out of range"); }
			return data[idx];
		}

		void PushBack(T elem)
		{
			if (capacity > size)
			{
				data[size] = elem;
				size++;
			}
			else
			{
				size_t newCapacity = 2 * capacity;
				T* newData = new T[newCapacity] {};

				for (size_t idx{}; idx < size; idx++)
				{
					newData[idx] = data[idx];
				}
				if (size < newCapacity)
				{
					newData[size] = elem;
				}

				delete[] data;

				capacity = newCapacity;
				size++;
				data = new T[capacity] {};

				for (size_t idx{}; idx < size; idx++)
				{
					data[idx] = newData[idx];
				}

				delete[] newData;
			}
		}

	private:
		T* data;
		size_t capacity;
		size_t size;
	};


	template <typename T>
	std::ostream& operator<< (std::ostream& stream, const Vector<T>& obj)
	{
		for (size_t idx{}; idx < obj.getSize(); idx++)
		{
			stream << obj.getElemAt(idx) << " ";
		}
		return stream;
	}
}

#endif