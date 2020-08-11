#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class CBox
{
public:
	// Destructor definition
	~CBox()
	{
		cout << "Destructor called." << endl;
	}

	// Constructor definition
	CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
		m_Length{ lv }, m_Width{ wv }, m_Height(hv)
	{
		cout << "Constructor called." << endl;
	}

	// Function to calculate the volume of a box
	double volume() const
	{
		return m_Length * m_Width * m_Height;
	}

	// Function to compare two boxes.  Return true if first letter is greater than the second letter, otherwise false
	bool compare(const CBox* pBox) const
	{
		if (!pBox)
		{
			return false;
		}
		return this->volume() > pBox->volume();
	}

private:
	double m_Length;
	double m_Width;
	double m_Height;
};

// Function to demonstrate the CBox class destructor in action
int main()
{
	CBox boxes[5];
	CBox cigar{ 8.0, 5.0, 1.0 };
	CBox match{ 2.2, 1.1, 0.5 };
	CBox* pB1{ &cigar };
	CBox* pB2{};

	cout << "Volume of a cigar box is " << pB1->volume() << endl;

	pB2 = boxes;
	boxes[2] = match;
	cout << "Volume of boxes[2] is " << (pB2 + 2)->volume() << endl;

	return 0;
}