#include "stdafx.h"
#include "Line.h"


CLine::CLine(const CPoint& start, const CPoint& end, COLORREF color, int penWidth, int a_penStyle) :
	CElement{ start, color, penWidth, a_penStyle }, m_EndPoint{ end }
{
	// Define enclosing rectangle
	m_EnclosingRect = CRect{ start, end };
	m_EnclosingRect.NormalizeRect();						// Normalize to ensure that left and top values are less than right and bottom values
	int width{ penWidth == 0 ? 1 : penWidth };				// Inflate rect by at least 1
	m_EnclosingRect.InflateRect(width, width);				// Enlarge by pen width
}


CLine::~CLine()
{
}


// Draw a CLine object
void CLine::Draw(CDC* pDC, std::shared_ptr <CElement> pElement)
{
	// Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };				// Select the pen

	// Now draw the line
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen);								// Restore the old pen
}

// Move a CLine object
void CLine::Move(const CSize& aSize)
{
	m_StartPoint += aSize;			// Move the start point
	m_EndPoint += aSize;			// Move the end point
	m_EnclosingRect += aSize;		// Move the enclosing rectangle
}