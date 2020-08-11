// Source.cpp
// Asks user to enter an integer.  Use Bitwise operator to determine the positive remainder when divided by 8.

#include <iostream>

using std::cout;
using std::cin;

int main()
{
	int userValue;

	cout << "Enter an integer (positive or negative): ";
	cin >> userValue;

	cout << "The remainder after dividing your number by 8 is "
		<< userValue - ((userValue >> 3) << 3)
		<< std::endl;

	return 0;
}