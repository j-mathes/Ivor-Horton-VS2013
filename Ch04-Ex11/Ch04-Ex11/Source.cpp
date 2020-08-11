#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

int main()
{
	int max{};
	cout << endl
		<< "Enter the number of primes you would like (at least 4): ";

	cin >> max;

	if (max < 4)
		max = 4;

	// allocate prime array and initialize with seed primes
	// a pointer to a long named pprime
	long* pprime{ new long[max] {2L, 3L, 5L} };

	long trial{ 5L };
	int count{ 3 };
	bool found{ false };

	do
	{
		trial += 2L;
		found = false;

		for (int i = 0; i < count; i++)
		{
			found = (trial % *(pprime + i)) == 0;
			if (found)
				break;
		}

		if (!found)
			*(pprime + count++) = trial;

	} while (count < max);

	// output primes 5 to a line
	for (int i = 0; i < max; i++)
	{
		if (i % 5 == 0)
			cout << endl;

		cout << setw(10) << *(pprime + i);
	}

	delete[] pprime;
	pprime = nullptr;
	cout << endl;

	return 0;
}