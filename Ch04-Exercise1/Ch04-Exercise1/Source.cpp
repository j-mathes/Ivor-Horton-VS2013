#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

int main()
{
	size_t arraySize{ 5 };								// initial size for the array
	double* values{ new double[arraySize] };			// initial array to store input values
	double* temp{};										// temporary store for pointer to new array
	double inputValue{};								// current input value
	size_t index{};										// index to the values array

	for(;;)
	{
		// read the next value
		cout << endl
			<< "Enter a value or 0 to stop: ";

		cin >> inputValue;

		// if the vallue is 0 we are done so exit the loop
		if (inputValue == 0.0)
			break;

		// store the value and increment the index
		values[index] = inputValue;
		index++;

		// if the index reaches arraySize we need a bigger array
		if (index == arraySize)
		{
			// increase the array size value
			//arraySize += 5;
			arraySize++;

			// allocate the new array
			temp = new double[arraySize];

			// copy the elements from the old array to the new array
			// to do this, iterate through the old array and at each index, copy values over one-by-one
			for (size_t i = 0; i < index; i++)
			{
				temp[i] = values[i];
			}
			// delete the old array
			delete[] values;

			// store the address of the new array
			values = temp;

			// reset temp to null
			temp = nullptr;
		}
	}

	// calculate the average and output the values
	double average{};

	for (size_t i = 0; i < index; i++)
	{
		average += values[i];
		cout << setw(10) << values[i];

		if ((i+1) % 5 == 0)
		{
			cout << endl;
		}
	}

	// output the average
	cout << endl
		<< "The average is " << average / index
		<< endl;

	// release the memory for the array
	delete[] values;

	// reset the array to null
	values = nullptr;

	return 0;
}