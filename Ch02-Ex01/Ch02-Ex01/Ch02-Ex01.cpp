// Ch02-Ex01.cpp
// A simple example of a program
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	int apples, oranges;		// define two integer variables
	int fruit;					// ... then another one

	apples = 5; oranges = 6;	// set initial values
	fruit = apples + oranges;	// get total amount of fruit

	cout << endl;				// start output on a new line
	cout << "Oranges are not the only fruit..." << endl
		 << "- and we have " << fruit << " fruits in all.";
	cout << endl;				// Output a nre line character

	return 0;
}