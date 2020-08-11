#include <iostream>
#include <new>
using std::cout;
using std::endl;
using std::bad_alloc;

int main()
{
	char* pdata{};
	size_t count{ ~static_cast<size_t>(0) / 2 };
	try
	{
		pdata = new char[count];
		cout << "Memory allocated." << endl;
	}
	catch (bad_alloc& ex)
	{
		cout << "Memory allocation failed." << endl
			<< "The information from the exception object is: "
			<< ex.what() << endl;
	}
	delete[] pdata;
	return 0;
}