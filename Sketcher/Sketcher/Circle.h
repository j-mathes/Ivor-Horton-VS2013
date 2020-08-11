#pragma once
#include "Element.h"
class CCircle :
	public CElement
{
public:
	virtual ~CCircle();
	virtual void Draw(CDC* pDC, std::shared_ptr < CElement> pElement=nullptr) override;		// Function to display a circle
	virtual void Move(const CSize& aSize) override;											// Function to move an element

	// Constructor for a circle object
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth, int a_penStyle = PS_SOLID);

protected:
	CCircle();				// Default constructor - should not be used
	CPoint m_BottomRight;		// Bottom point for defining circle
};

