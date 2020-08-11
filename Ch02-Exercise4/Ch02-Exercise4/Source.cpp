#include <iostream>

int main()
{
	int width{ 1280 };
	int height{ 1024 };

	double aspect{ static_cast<double>(width) / height };
	std::cout << "The aspect ratio is " << aspect << std::endl;

	return 0;
}