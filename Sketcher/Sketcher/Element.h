#pragma once
#include <memory>

static const COLORREF SELECT_COLOR{ RGB(255, 0, 180) };		//Highlight color

// CElement command target

class CElement : public CObject
{
protected:
	CPoint m_StartPoint;					// Element position
	int m_PenWidth;							// Pen width
	COLORREF m_Color;						// Color of an element
	int m_PenStyle;							// Style of pen
	CRect m_EnclosingRect;					// Bounding box of element

public:
	virtual ~CElement();
	virtual void Draw(CDC* pDC, std::shared_ptr < CElement> pElement=nullptr) {}			// Virtual draw operation
	virtual void Move(const CSize& aSize) {}												// Move an element

	// Get the element bounding box
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }

protected:
	// Constructors protected so they cannot be called outside the class
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1, int m_PenStyle = PS_SOLID );

	// Create a pen
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement)
	{
		if (!aPen.CreatePen(m_PenStyle, m_PenWidth, this == pElement.get()? SELECT_COLOR : m_Color))
		{
			// Pen creation failed
			AfxMessageBox(_T("Pen creation failed."), MB_OK);
			AfxAbort();
		}
	}
};


