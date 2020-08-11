#include "Box.h"
#include <algorithm>

CBox::CBox(double lv, double wv, double hv)
	: m_Length{std::max(lv, wv)}
	, m_Width{std::min(lv, wv)}
	, m_Height{hv}
{
	if (lv < 0.0 || wv < 0.0 || hv < 0.0)
	{
		throw "Negative dimension specified for CBox object.";
		// Ensure the height is <= width is <= length
		if (m_Height > m_Length)
		{
			std::swap(m_Height, m_Length);
		}
		else if (m_Height > m_Width)
		{
			std::swap(m_Height, m_Width);
		}
	}
}


CBox::~CBox()
{
}


// Addition operator for CBox objects
CBox CBox::operator+(const CBox& aBox) const
{
	return CBox{ std::max(m_Length, aBox.m_Length),
				std::max(m_Width, aBox.m_Width),
				m_Height + aBox.m_Height};
}


// Multiplication operator for CBox objects
CBox CBox::operator*(int n) const
{
	if (n % 2)
		return CBox{ m_Length, m_Width, n*m_Height };			// odd
	else
		return CBox{ m_Length, 2.0*m_Width, (n / 2)*m_Height };	// even
}


// Division operator for CBox objects
int CBox::operator/(const CBox& aBox) const
{
	// Number of boxes in horizontal plane this way
	int tc1{ static_cast<int>((m_Length / aBox.m_Length))*
		static_cast<int>((m_Width / aBox.m_Width)) };
	// Number of boxes in horizontal plane that way
	int tc2{ static_cast<int>((m_Length / aBox.m_Width))*
		static_cast<int>((m_Width / aBox.m_Length)) };
	//Return best fit
	return static_cast<int>((m_Height / aBox.m_Height)*(tc1 > tc2 ? tc1 : tc2));
}
