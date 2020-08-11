#include <iostream>
#include <utility>
#include <algorithm>

using std::cout;
using std::endl;
using namespace std::rel_ops;

class CBox
{
public:
	// Constructor Definition
	explicit CBox(double lv = 1.0, double wv = 1.0, double hv = 1.0) :
		m_Length{ std::max(lv, wv) }, m_Width{ std::min(lv, wv) }, m_Height{ hv }
	{
		if (m_Height > m_Length)
		{
			std::swap(m_Height, m_Length);
			std::swap(m_Width, m_Height);
		}
		else if (m_Height > m_Width)
			std::swap(m_Height, m_Width);
	}

	// Functions below are declared as 'const' because they don't modify any data members
	double volume() const
	{
		return m_Length * m_Width * m_Height;
	}

	bool operator<(const CBox& aBox) const
	{
		return this->volume() < aBox.volume();
	}

	bool operator<(const double value) const
	{
		return this->volume() < value;
	}

	bool operator>(const double value)	const
	{
		return this->volume() > value;
	}

	bool operator==(const CBox& abox) const
	{
		return this->volume() == abox.volume();
	}

	CBox operator+(const CBox& aBox) const
	{
		return CBox(std::max(m_Length, aBox.m_Length),
			std::max(m_Width, aBox.m_Width),
			m_Height + aBox.m_Height);
	}

	void showBox() const
	{
		cout << m_Length << " " << m_Width << " " << m_Height << endl;
	}

private:
	double m_Length;
	double m_Width;
	double m_Height;
};


// CSamples template definition
template <typename T> class CSamples
{
public:
	// Constructors
	CSamples(const T values[], int count);
	CSamples(const T& value);
	CSamples(T&& value);
	CSamples() = default;

	bool add(const T& value);
	bool add(T&& value);
	T max() const;

private:
	static const size_t maxSamples{ 100 };
	T m_Values[maxSamples];
	int m_Next {};
};

template<typename T>
CSamples<T>::CSamples(const T values[], int count)
{
	m_Next = count < maxSamples ? count : maxSamples;
	for (int i = 0; i < m_Next; i++)
	{
		m_Values[i] = values[i];
	}
}

template<typename T>
CSamples<T>::CSamples(const T & value)
{
	m_Values[0] = value;
	m_Next = 1;
}

template<typename T>
CSamples<T>::CSamples(T && value)
{
	cout << "Move constructor." << endl;
	m_Values[0] = std::move(value);
	m_Next = 1;
}

template<typename T>
bool CSamples<T>::add(const T & value)
{
	cout << "Add." << endl;
	bool OK{ m_Next < maxSamples };
	if (OK)
		m_Values[m_Next++] = value;
	return OK;
}

template<typename T>
bool CSamples<T>::add(T && value)
{
	cout << "Add move." << endl;
	bool OK{ m_Next < maxSamples };
	if (OK)
	{
		m_Values[m_Next++] = std::move(value);
	}
	return OK;
}

template<typename T>
T CSamples<T>::max() const
{
	T theMax{ m_Values[0] };
	for (int i = 1; i < m_Next; i++)
	{
		if (theMax < m_Values[i])
			theMax = m_Values[i];
	}
	return theMax;
}

int main()
{
	CBox boxes[]
	{
		CBox {8.0, 5.0, 2.0},
		CBox {5.0, 4.0, 6.0},
		CBox {4.0, 4.0, 3.0}
	};

	CSamples<CBox> myBoxes{ boxes, _countof(boxes) };

	CBox maxBox{ myBoxes.max() };
	cout << "The biggest box has a volume of "
		<< maxBox.volume() << endl;
	
	CSamples<CBox> moreBoxes{ CBox { 8.0, 5.0, 2.0} };
	moreBoxes.add(CBox{ 5.0, 4.0, 6.0 });
	moreBoxes.add(CBox{ 4.0, 3.0, 3.0 });
	
	cout << "The biggest box has a volume of "
		<< moreBoxes.max().volume() << endl;

	return 0;
}
