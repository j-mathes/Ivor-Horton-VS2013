#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	virtual ~CRectangle();
	virtual void Draw(CDC* pDC, std::shared_ptr <CElement> pElement=nullptr) override;			// Function to display a rectangle
	virtual void Move(const CSize& aSize) override;											// Function to move an element

	// Constructor for a rectangle object
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth, int a_penStyle = PS_SOLID);

protected:
	CRectangle();									// Default constructor - should not be used
	CPoint m_BottomRight;							// Bottom-right point for the rectangle
};

