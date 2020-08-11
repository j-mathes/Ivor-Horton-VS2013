#include <iostream>
using std::cout;
using std::endl;

long sum(long a, long b);				// function prototype
long product(long a, long b);			// function prototype

int main()
{
	long(*pdo_it) (long, long);			// pointer to function declaration

	pdo_it = product;

	cout << endl
		<< "3*5 + " << pdo_it(3, 5);	// call product through a pointer

	pdo_it = sum;						// reassign pointer to sum();
	cout << endl
		<< "3+5 = "
		<< pdo_it(3, 5);

	cout << endl;

	return 0;
}

long sum(long a, long b)
{
	return a + b;
}

long product(long a, long b)
{
	return a * b;
}
