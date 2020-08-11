// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"


// CElement

CElement::CElement()
{
}

CElement::CElement(const CPoint & start, COLORREF color, int penWidth, int penStyle) :
	m_StartPoint {start}, m_PenWidth {penWidth}, m_Color {color}, m_PenStyle{penStyle}
{
}

CElement::~CElement()
{
}


// CElement member functions
