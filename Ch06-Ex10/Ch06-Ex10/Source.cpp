// Ex6_10.cpp
// A program to implement a calculator

#include <iostream>
#include <cstdlib>								// For the exit() function
#include <cctype>								// For the isdigit() function
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

void eatspaces(char* str);						// Function to eliminate blanks
double expr(char* str);							// Function evaluating an expression
double term(const char* str, size_t& index);	// Function analyzing a term
double number(const char* str, size_t& index);	// Function to recognize a number

const size_t MAX{ 80 };							// Maximum expression length,
												// including '\0'

int main()
{
	char buffer[MAX]{};

	cout << endl
		<< "Welcome to Calculator."
		<< endl
		<< "Enter an expression, or an empty line to quit."
		<< endl;

	for (;;)
	{
		cin.getline(buffer, sizeof buffer);
		eatspaces(buffer);

		if (!buffer[0])
		{
			return 0;
		}

		try
		{
			cout << "\t= " << expr(buffer)
				<< endl << endl;
		}
		catch (const char* pEx)
		{
			cerr << pEx << endl;
			cerr << "Ending program." << endl;
			return 1;
		}
	}
}

void eatspaces(char * str)
{
	size_t i{};
	size_t j{};

	while ((*(str + i) = *(str + j++)) != '\0')
		if (*(str + i) != ' ')
			i++;
	return;
}

double expr(char * str)
{
	double value{};
	size_t index{};

	value = term(str, index);

	for (;;)
	{
		switch (*(str + index++))
		{
		case '\0':
				return value;

		case '+':
			value += term(str, index);
			break;

		case '-':
			value -= term(str, index);
			break;

		default:
			char message[38]{ "Expression evaluation error. Found: " };
			strncat_s(message, str + index - 1, 1);
			throw message;
			break;
		}
	}
}

double term(const char * str, size_t & index)
{
	double value{};

	value = number(str, index);

	while (true)
	{
		if (*(str + index) == '*')
			value *= number(str, ++index);
		else if (*(str + index) == '/')
			value /= number(str, ++index);
		else
			break;
	}
	return value;
}

double number(const char * str, size_t & index)
{
	double value{};

	if (!isdigit(*(str + index)))
	{
		char message[31]{ "Invalid character in number: " };
		strncat_s(message, str + index, 1);
		throw message;
	}

	while (isdigit(*(str + index)))
		value = 10 * value + (*(str + index++) - '0');

	if (*(str + index) != '.')
		return value;

	double factor{ 1.0 };
	while (isdigit(*(str + (++index))))
	{
		factor *= 0.1;
		value = value + (*(str + index) - '0') * factor;
	}

	return value;
}
