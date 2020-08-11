#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

struct Sample
{
	int value1;
	int value2;
	char* sPtr;
};

void showSample(Sample* sample);

int main()
{
	Sample a{ 0, 0 };
	char* s{ "Hello World!" };
	a.sPtr = s;

	Sample b{ 0, 0 };

	a.value1 = 10;
	b.value1 = 30;

	cout << endl << "Sample a, value 1: " << a.value1;
	cout << endl << "Sample a, value 2: " << a.value2;
	cout << endl << "Sample b, value 1: " << b.value1;
	cout << endl << "Sample b, value 2: " << b.value2;
	
	a.value2 = a.value1;
	b.value2 = b.value1;

	cout << endl;
	cout << endl << "Sample a, value 1: " << a.value1;
	cout << endl << "Sample a, value 2: " << a.value2;
	cout << endl << "Sample b, value 1: " << b.value1;
	cout << endl << "Sample b, value 2: " << b.value2;
	cout << endl;

	b = a;
	b.sPtr = new char[strlen(a.sPtr) + 1];			// defines new memory to hold character array
	strcpy_s(b.sPtr, strlen(a.sPtr) + 1, a.sPtr);	// copies the string data from A into B.  This way they point to two different strings.

	a.sPtr = "Change";

	cout << b.sPtr << endl;
	cout << a.sPtr << endl;

	showSample(&a);
	showSample(&b);

	return 0;
}

void showSample(Sample* sample)
{
	cout << endl << "Sample, value 1: " << sample->value1;
	cout << endl << "Sample, value 2: " << sample->value2;
	cout << endl << "Sample, value 2: " << sample->sPtr;
	cout << endl;
}