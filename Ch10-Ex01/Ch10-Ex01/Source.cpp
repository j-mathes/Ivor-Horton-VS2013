#include <iostream>
#include <vector>
using std::vector;

template<class T>
void listInfo(const vector<T>& v)
{
	std::cout << "Container capacity: " << v.capacity() << " size: " << v.size() << std::endl;
}

int main()
{
	vector<double> data;
	listInfo(data);

	data.reserve(100);
	listInfo(data);

	vector<int> numbers(10, -1);
	std::cout << "The initial values are: ";

	for (auto n:numbers)
	{
		std::cout << " " << n;
	}
	std::cout << std::endl << std::endl;

	auto oldC = numbers.capacity();
	auto newC = oldC; listInfo(numbers);

	for (int i = 0; i < 1000; i++)
	{
		numbers.push_back(2 * i);
		newC = numbers.capacity();
		if (oldC < newC)
		{
			oldC = newC;
			listInfo(numbers);
		}
	}
}