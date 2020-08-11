#include "stdafx.h"
#include "Ellipse.h"
#include <algorithm>
#include <cmath>


CEllipse::CEllipse(const CPoint & start, const CPoint & end, COLORREF color, int penWidth, int a_penStyle) :
	CElement{ start, color, penWidth, a_penStyle }
{
	// Same procedure as drawing a rectangle.  The points we definde will be fed to the draw ellipse function instead of a draw rectangle function
	// Normalize the rectangle defining points
	m_StartPoint = CPoint{ (std::min)(start.x, end.x), (std::min)(start.y, end.y) };
	m_BottomRight = CPoint{ (std::max)(start.x, end.x), (std::max)(start.y, end.y) };

	// Ensure the width and height between points is at least 2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
	{
		m_BottomRight.x = m_StartPoint.x + 2;
	}
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
	{
		m_BottomRight.y = m_StartPoint.y + 2;
	}

	// Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	int width{ penWidth == 0 ? 1 : penWidth };
	m_EnclosingRect.InflateRect(width, width);
}

CEllipse::CEllipse()
{
}


CEllipse::~CEllipse()
{
}

// Draw an ellipse - exact same as for drawing a circle, we just feed it proper points
void CEllipse::Draw(CDC* pDC, std::shared_ptr <CElement> pElement)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen, pElement);
	CPen* pOldPen{ pDC->SelectObject(&aPen) }; // Select the pen
											   // Select a null brush
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };
	// Now draw the ellipse
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
		m_BottomRight.x, m_BottomRight.y);
	pDC->SelectObject(pOldPen); // Restore the old pen
	pDC->SelectObject(pOldBrush); // Restore the old brush
}

// Move a CEllipse object
void CEllipse::Move(const CSize& aSize)
{
	m_StartPoint += aSize;			// Move the start point
	m_BottomRight += aSize;			// Move the bottom right
	m_EnclosingRect += aSize;		// Move the enclosing rectangle
}