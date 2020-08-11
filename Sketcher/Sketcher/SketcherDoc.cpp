
// SketcherDoc.cpp : implementation of the CSketcherDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "PenDialog.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CSketcherDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CSketcherDoc::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcherDoc::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcherDoc::OnColorBlue)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketcherDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnElementRectangle)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnElementCircle)
	ON_COMMAND(ID_ELEMENT_CURVE, &CSketcherDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CSketcherDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcherDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcherDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcherDoc::OnUpdateColorBlue)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcherDoc::OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnUpdateElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnUpdateElementCircle)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketcherDoc::OnUpdateElementCurve)
	ON_COMMAND(ID_ELEMENT_ELLIPSE, &CSketcherDoc::OnElementEllipse)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_ELLIPSE, &CSketcherDoc::OnUpdateElementEllipse)
	ON_COMMAND(ID_PENSTYLE_SOLID, &CSketcherDoc::OnPenstyleSolid)
	ON_COMMAND(ID_PENSTYLE_DASHED, &CSketcherDoc::OnPenstyleDashed)
	ON_COMMAND(ID_PENSTYLE_DOTTED, &CSketcherDoc::OnPenstyleDotted)
	ON_COMMAND(ID_PENSTYLE_DASH_DOTTED, &CSketcherDoc::OnPenstyleDashDotted)
	ON_COMMAND(ID_PENSTYLE_DASH_DOT_DOTTED, &CSketcherDoc::OnPenstyleDashDotDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_SOLID, &CSketcherDoc::OnUpdatePenstyleSolid)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASHED, &CSketcherDoc::OnUpdatePenstyleDashed)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DOTTED, &CSketcherDoc::OnUpdatePenstyleDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASH_DOTTED, &CSketcherDoc::OnUpdatePenstyleDashDotted)
	ON_UPDATE_COMMAND_UI(ID_PENSTYLE_DASH_DOT_DOTTED, &CSketcherDoc::OnUpdatePenstyleDashDotDotted)
	ON_COMMAND(ID_PEN_WIDTH, &CSketcherDoc::OnPenWidth)
	ON_COMMAND(ID_ELEMENT_TEXT, &CSketcherDoc::OnElementText)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_TEXT, &CSketcherDoc::OnUpdateElementText)
END_MESSAGE_MAP()


// CSketcherDoc construction/destruction

CSketcherDoc::CSketcherDoc()
{
	// TODO: add one-time construction code here

}

CSketcherDoc::~CSketcherDoc()
{
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketcherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSketcherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcherDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketcherDoc diagnostics

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc commands


void CSketcherDoc::OnColorBlack()
{
	m_Color = ElementColor::BLACK;			// Set the drawing color to black
}


void CSketcherDoc::OnColorRed()
{
	m_Color = ElementColor::RED;			// Set the drawing color to red
}


void CSketcherDoc::OnColorGreen()
{
	m_Color = ElementColor::GREEN;			// Set the drawing color to green
}


void CSketcherDoc::OnColorBlue()
{
	m_Color = ElementColor::BLUE;			// Set the drawing color to blue
}


void CSketcherDoc::OnElementLine()
{
	m_Element = ElementType::LINE;			// Set element type as a line
}


void CSketcherDoc::OnElementRectangle()
{
	m_Element = ElementType::RECTANGLE;		// Set element type as a rectangle
}


void CSketcherDoc::OnElementCircle()
{
	m_Element = ElementType::CIRCLE;		// Set element type as a circle
}


void CSketcherDoc::OnElementCurve()
{
	m_Element = ElementType::CURVE;			// Set element type as a curve
}

void CSketcherDoc::OnElementEllipse()
{
	m_Element = ElementType::ELLIPSE;		// Set element type as an ellipse
}


void CSketcherDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is black
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}


void CSketcherDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is red
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CSketcherDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is green
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CSketcherDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current color is blue
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}


void CSketcherDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current element type is line
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CSketcherDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current element type is rectangle
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}


void CSketcherDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current element type is circle
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}


void CSketcherDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current element type is curve
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}



void CSketcherDoc::OnUpdateElementEllipse(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current element type is ellipse
	pCmdUI->SetCheck(m_Element == ElementType::ELLIPSE);
}


void CSketcherDoc::OnPenstyleSolid()
{
	// Set pen style as Solid
	m_PenStyle = PS_SOLID;
}


void CSketcherDoc::OnPenstyleDashed()
{
	// Set pen style as Dashed
	m_PenStyle = PS_DASH;
}


void CSketcherDoc::OnPenstyleDotted()
{
	// Set pen style as Dotted
	m_PenStyle = PS_DOT;
}


void CSketcherDoc::OnPenstyleDashDotted()
{
	// Set pen style as Dash-Dotted
	m_PenStyle = PS_DASHDOT;
}


void CSketcherDoc::OnPenstyleDashDotDotted()
{
	// Set pen style as Solid
	m_PenStyle = PS_DASHDOTDOT;
}


void CSketcherDoc::OnUpdatePenstyleSolid(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current pen style is Solid
	pCmdUI->SetCheck(m_PenStyle == PS_SOLID);
}


void CSketcherDoc::OnUpdatePenstyleDashed(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current pen style is Dashed
	pCmdUI->SetCheck(m_PenStyle == PS_DASH);
}


void CSketcherDoc::OnUpdatePenstyleDotted(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current pen style is Dotted
	pCmdUI->SetCheck(m_PenStyle == PS_DOT);
}


void CSketcherDoc::OnUpdatePenstyleDashDotted(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current pen style is Dash-Dotted
	pCmdUI->SetCheck(m_PenStyle == PS_DASHDOT);
}


void CSketcherDoc::OnUpdatePenstyleDashDotDotted(CCmdUI *pCmdUI)
{
	// Set menu item Checked if the current pen style is Dash-Dot-Dotted
	pCmdUI->SetCheck(m_PenStyle == PS_DASHDOTDOT);
}


void CSketcherDoc::OnPenWidth()
{
	CPenDialog aDlg;					// Create a local dialog box
	
	// Set pen width in the dialog to that in the document
	aDlg.m_PenWidth = m_PenWidth;

	if (aDlg.DoModal() == IDOK)			// Display the dialog box as modal
		m_PenWidth = aDlg.m_PenWidth;	// When closed with OK, get the pen width
}


void CSketcherDoc::OnElementText()
{
	m_Element = ElementType::TEXT;
}


void CSketcherDoc::OnUpdateElementText(CCmdUI *pCmdUI)
{
	// Set checked if the current element is text
	pCmdUI->SetCheck(m_Element == ElementType::TEXT);
}
