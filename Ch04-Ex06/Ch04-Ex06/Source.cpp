#include <iostream>

using std::cout;
using std::endl;
using std::hex;							// hex representation manipulator
using std::dec;							// decimal representation manipulator

int main()
{
	long* pnumber{};					// pointer to a long variable initialized to nothing
	long number1{ 55 }, number2{ 99 };	// two long variables defined

	pnumber = &number1;					// pnumber now holds the address of number1 variable
	*pnumber += 11;						// 11 added to the contents of variable pointed to by pnumber (in this case number1)
	cout << endl
		<< "number1 = " << number1
		<< "   &number1 = " << hex << pnumber;	// showing the address of number1 variable by showing the contents of the pointer variable pnumber

	pnumber = &number2;					// change the pointer to address of number2
	number1 = *pnumber * 10;			// number1 is now equal to the contents of the variable referenced by pnumber (in this case number2) and then multiplied by 10

	cout << endl
		<< "number1 = " << dec << number1
		<< "   pnumber = " << hex << pnumber	// this will show the address held in pnumber, which is the address of number2
		<< "   *pnumber = " << dec << *pnumber;	// this will show the contents of the variable address held in pnumber (in this case number2)

	cout << endl;

	return 0;
}