// Source.cpp
// Asks user to enter a number and then prints it out, using an integer as a local variable

#include <iostream>

int main()
{
	int userNumber;
	bool isSuccessful = false;

	while (!isSuccessful)
	{
		std::cout << "Please enter a number: ";

		std::cin >> userNumber;
		
		isSuccessful = true;
	}

	std::cout << std::endl << "The number you entered is " << userNumber << std::endl;

	return 0;
}