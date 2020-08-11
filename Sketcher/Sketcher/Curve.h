#pragma once
#include "Element.h"
#include <vector>

class CCurve :
	public CElement
{
public:
	virtual ~CCurve();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;					// Function to display a curve
	virtual void Move(const CSize& aSize) override;											// Function to move an element

	// Constructor for a curve object
	CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penWidth, int a_penStyle = PS_SOLID);

	void AddSegment(const CPoint& point);					// Add a segment to the curve

protected:
	std::vector<CPoint> m_Points;							// Points defininf the curve
	CCurve();												// Default constructor - should not be used
};

