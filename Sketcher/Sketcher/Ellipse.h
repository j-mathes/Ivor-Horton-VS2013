#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
public:
	virtual ~CEllipse();
	virtual void Draw(CDC* pDC, std::shared_ptr <CElement> pElement = nullptr) override;			// Function to display an ellipse
	virtual void Move(const CSize& aSize) override;											// Function to move an element

	// Constructor for an ellipse object
	CEllipse(const CPoint& start, const CPoint& end, COLORREF color, int penWidth, int a_penStyle = PS_SOLID);

protected:
	CEllipse();										// Default constructor - should not be used
	CPoint m_BottomRight;							// Bottom-right point for the ellipse
};

