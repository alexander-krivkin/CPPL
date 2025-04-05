#include <iostream>


struct test_struct
{
	double a{ 10.1 }, b{ 20.2 };
};


namespace ak
{
	template <typename T>
	class unique_ptr final
	{
	public:
		unique_ptr() = delete;
		explicit unique_ptr(T* ptr) : _ptr(ptr) {}
		explicit unique_ptr(const unique_ptr<T>&) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;
		virtual ~unique_ptr() { std::cout << "unique_ptr destructed" << std::endl; delete _ptr; }

		T& operator*() const { return *_ptr; }
		T* operator->() const { return _ptr; }
		T* release() { T* _tmp_ptr = _ptr; _ptr = nullptr; return _tmp_ptr; }

	private:
		T* _ptr;
	};
}


int main()
{
	ak::unique_ptr<test_struct> pTS1(new test_struct);
	auto TS = *pTS1;
	auto pTS2 = pTS1.release();
	pTS2->a = 333;

	return EXIT_SUCCESS;
}