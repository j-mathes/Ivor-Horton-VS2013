#include <iostream>
#include "CandyBox.h"

int main()
{
	CBox myBox{ 4.0, 3.0, 2.0 };
	CCandyBox myCandyBox;
	CCandyBox myMintBox{ "Wafer Thin Mints" };

	std::cout << "myBox occupies " << sizeof myBox
		<< " bytes" << std::endl // the objects require
		<< "myCandyBox occupies " << sizeof myCandyBox
		<< " bytes" << std::endl
		<< "myMintBox occupies " << sizeof myMintBox
		<< " bytes" << std::endl;
	std::cout << "myBox length is " << myBox.m_Length << std::endl;

	myBox.m_Length = 10.0;

	myCandyBox.m_Length = 10.0;

	return 0;
}