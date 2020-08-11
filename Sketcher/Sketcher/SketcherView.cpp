// SketcherView.cpp : implementation of the CSketcherView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "SketcherView.h"
#include "Line.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Curve.h"
#include "Ellipse.h"
#include "ScaleDialog.h"
#include "Text.h"
#include "TextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CScrollView)

BEGIN_MESSAGE_MAP(CSketcherView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ELEMENT_MOVE, &CSketcherView::OnElementMove)
	ON_COMMAND(ID_ELEMENT_DELETE, &CSketcherView::OnElementDelete)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ELEMENT_SENDTOBACK, &CSketcherView::OnElementSendtoback)
	ON_COMMAND(ID_VIEW_SCALE, &CSketcherView::OnViewScale)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SCALE, &CSketcherView::OnUpdateScale)
END_MESSAGE_MAP()

// CSketcherView construction/destruction

CSketcherView::CSketcherView()
	: m_FirstPoint(0)
{
	SetScrollSizes(MM_TEXT, CSize{});
}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketcherView drawing

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// Draw the sketch
	//for (auto iter = pDoc->begin(); iter !=pDoc->end(); iter++)
		for (const auto& pElement : *pDoc)
		{
			if (pDC->RectVisible(pElement->GetEnclosingRect()))			// Element visable?
				pElement->Draw(pDC, m_pSelected);						// Yes, draw it
		}
}


// CSketcherView printing

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSketcherView diagnostics

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView message handlers


void CSketcherView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this == GetCapture())
	{
		ReleaseCapture();			// Stop capturing mouse messages
	}

	// Make sure there is an element
	if (m_pTempElement)
	{
		CRect aRect{ m_pTempElement->GetEnclosingRect() };		// Get enclosing rectangle
		GetDocument()->AddElement(m_pTempElement);				// Add element pointer to sketch

		CClientDC aDC{ this };			// Create a device context
		OnPrepareDC(&aDC);				// Get origin adjusted
		aDC.LPtoDP(aRect);				// Convert to client coordinates
		InvalidateRect(aRect);			// Get the area redrawn
		m_pTempElement.reset();			// Reset the element pointer
	}
}


void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC aDC{ this };				// Create a device context
	OnPrepareDC(&aDC);					// Get origin adjusted
	aDC.DPtoLP(&point);					// Convert point to logical coordinates
	CSketcherDoc* pDoc{ GetDocument() };// Get a document pointer

	if (m_MoveMode)
	{
		// In moving mode, so drop the element
		m_MoveMode = false;				// end move mode
		auto pElement(m_pSelected);		// Store selected address
		m_pSelected.reset();			// De-select the element pointer
		pDoc->UpdateAllViews(nullptr, 0, pElement.get());				// Redraw all the views
		//GetDocument()->UpdateAllViews(nullptr, 0, pElement.get());		// Redraw all the views
	}
	else if (pDoc->GetElementType()==ElementType::TEXT)
	{
		CTextDialog aDlg;
		if (aDlg.DoModal()==IDOK)
		{
			// Exit OK so create a text element
			CSize textExtent{ aDC.GetOutputTextExtent(aDlg.m_TextString) };
			textExtent.cx *= m_Scale;
			textExtent.cy *= m_Scale;
			std::shared_ptr<CElement> pTextElement{ std::make_shared<CText>(point, point + textExtent, aDlg.m_TextString, static_cast<COLORREF>(pDoc->GetElementColor())) };

			pDoc->AddElement(pTextElement);							// Add the element to the document
			pDoc->UpdateAllViews(nullptr, 0, pTextElement.get());	// Update all views
		}
	}
	else
	{
		m_FirstPoint = point;			// Record the cursor position
		SetCapture();					// Capture the mouse messages
	}
}


void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
	// Define a device context object for the view
	CClientDC aDC{ this };			// DC for this view
	OnPrepareDC(&aDC);				// Get origin adjusted
	aDC.DPtoLP(&point);				// Convert point to logical coordinates

	// If we are in move mode, move the selected element
	if (m_MoveMode)
	{
		MoveElement(aDC, point);		// Move the element
	}
	else if ((nFlags & MK_LBUTTON) && (this == GetCapture()))	// Verify the left button is down
	{
		m_SecondPoint = point;			// Save the current position
		if (m_pTempElement)
		{
			// An element was created previously
			if (ElementType::CURVE == GetDocument()->GetElementType())		// Is it a curve?
			{
				// We are drawing a curve so add a segment to the existing curve
				std::dynamic_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);									// Now we draw it
				return;														// We are done
			}
			else
			{
				// If we get here it's not a curve so redraw the old element so it dissappears from the view
				aDC.SetROP2(R2_NOTXORPEN);			// Set the drawing mode
				m_pTempElement->Draw(&aDC);			// Redraw the old element to erase it
			}
		}

		// Create a temporary element of the type and color that is recorded in the document object, and draw it
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
	else
	{
		// We are not creating an element, so do highlighting
		auto pOldSelected = m_pSelected;			// Copy previous
		m_pSelected = GetDocument()->FindElement(point);
		if (m_pSelected != pOldSelected)
		{
			if (m_pSelected)
			{
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelected.get());
			}
			if (pOldSelected)
			{
				GetDocument()->UpdateAllViews(nullptr, 0, pOldSelected.get());
			}
		}
	}
}


std::shared_ptr<CElement> CSketcherView::CreateElement() const
{

	// Get a pointer to the document for this view
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);								// Verify the pointer is good
													// Get the current element color
	COLORREF color{ static_cast<COLORREF>(pDoc->GetElementColor()) };
	int penWidth{ pDoc->GetPenWidth() };			// Get current pen width
	// Now select the element using the type stored in the document
	switch (pDoc->GetElementType())
	{
	case ElementType::RECTANGLE:
		return std::make_shared<CRectangle>(m_FirstPoint, m_SecondPoint, color, penWidth, pDoc->GetLineStyle());
	case ElementType::CIRCLE:
		return std::make_shared<CCircle>(m_FirstPoint, m_SecondPoint, color, penWidth, pDoc->GetLineStyle());
	case ElementType::CURVE:
		return std::make_shared<CCurve>(m_FirstPoint, m_SecondPoint, color, penWidth, pDoc->GetLineStyle());
	case ElementType::LINE:
		return std::make_shared<CLine>(m_FirstPoint, m_SecondPoint, color, penWidth, pDoc->GetLineStyle());
	case ElementType::ELLIPSE:
		return std::make_shared<CEllipse>(m_FirstPoint, m_SecondPoint, color, penWidth, pDoc->GetLineStyle());
	default:
		// Something's gone wrong
		AfxMessageBox(_T("Bad Element code"), MB_OK);
		AfxAbort();
		return nullptr;
	}

}


void CSketcherView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// Invalidate the area corresponding to the element pointed to by the thrid argument, otherwise the whole client area
	if (pHint)
	{
		CClientDC aDC{ this };				// Create a device context
		OnPrepareDC(&aDC);					// Get origin adjusted

		// Get the enclosing rectangle and convert it to client coordinates
		CRect aRect{ dynamic_cast<CElement*>(pHint)->GetEnclosingRect() };
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);				// Get the area redrawn
	}
	else
	{
		InvalidateRect(nullptr);
	}
}

void CSketcherView::MoveElement(CClientDC & aDC, const CPoint & point)
{
	CSize distance{ point - m_CursorPos };			// Get move distance
	m_CursorPos = point;							// Set the current point as 1st for next time

	// If there is an element selected, move it
	if (m_pSelected)
	{
		CSketcherDoc* pDoc{ GetDocument() };		// Get the document pointer

		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());		// Update all except this

		if (typeid(*(m_pSelected.get())) == typeid(CText))
		{
			// The element is text so use this method
			CRect oldRect{ m_pSelected->GetEnclosingRect() };	// Get old bounding rectangle
			aDC.LPtoDP(oldRect);								// Convert to client coordinates
			m_pSelected->Move(distance);						// Move the element
			InvalidateRect(&oldRect);

			UpdateWindow();										// Redraw immediately
			m_pSelected->Draw(&aDC, m_pSelected);				// Draw highlighted
		}
		else
		{
			// It is not text so use the ROP method
			aDC.SetROP2(R2_NOTXORPEN);
			m_pSelected->Draw(&aDC, m_pSelected);		// Draw element to erase it
			m_pSelected->Move(distance);				// Now move the element
			m_pSelected->Draw(&aDC, m_pSelected);		// Draw the moved element
		}
		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());		// Update all except this
	}
}


void CSketcherView::OnInitialUpdate()
{
	ResetScrollSizes();
	CScrollView::OnInitialUpdate();
}


void CSketcherView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);		// Load the context menu
	CMenu* pContext{};
	if (m_pSelected)
	{
		pContext = menu.GetSubMenu(0);
	}
	else
	{
		pContext = menu.GetSubMenu(1);

		// Check color menu items
		ElementColor color{ GetDocument()->GetElementColor() };
		menu.CheckMenuItem(ID_COLOR_BLACK, (ElementColor::BLACK == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_RED, (ElementColor::RED == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_GREEN, (ElementColor::GREEN == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_BLUE, (ElementColor::BLUE == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);

		// Check element menu items
		ElementType type{ GetDocument()->GetElementType() };
		menu.CheckMenuItem(ID_ELEMENT_LINE, (ElementType::LINE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE, (ElementType::RECTANGLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE, (ElementType::CIRCLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CURVE, (ElementType::CURVE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_ELLIPSE, (ElementType::ELLIPSE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_TEXT, (ElementType::TEXT == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}

	ASSERT(pContext != nullptr);			// Ensure it's there

	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}


void CSketcherView::OnElementMove()
{
	CClientDC aDC{ this };
	OnPrepareDC(&aDC);						// Set up the device context
	GetCursorPos(&m_CursorPos);				// Get cursor position in screen coordinates
	ScreenToClient(&m_CursorPos);			// Convert to client coordinates
	aDC.DPtoLP(&m_CursorPos);				// Convert to logical
	m_FirstPos = m_CursorPos;				// Remember the first position
	m_MoveMode = true;						// Start move mode
}


void CSketcherView::OnElementDelete()
{
	if (m_pSelected)
	{
		GetDocument()->DeleteElement(m_pSelected);			// Delete the element
		m_pSelected.reset();								// Changes smart pointer to nullptr
	}
}


void CSketcherView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_MoveMode)
	{
		// In moving mode, so drop the element back in original position
		CClientDC aDC{ this };
		OnPrepareDC(&aDC);						// Get origin adjusted
		MoveElement(aDC, m_FirstPos);			// Move element to original position
		m_pSelected.reset();					// De-select the element
		GetDocument()->UpdateAllViews(nullptr);	// Redraw all views
	}
}


void CSketcherView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_MoveMode)
	{
		m_MoveMode = false;
	}
	else
	{
		CScrollView::OnRButtonUp(nFlags, point);
	}
}


void CSketcherView::OnElementSendtoback()
{
	GetDocument()->SendToBack(m_pSelected);		// Move element to the end of list
}


void CSketcherView::OnViewScale()
{
	CScaleDialog aDlg;
	aDlg.m_Scale = m_Scale;
	if (aDlg.DoModal() == IDOK)
	{
		m_Scale = aDlg.m_Scale;
		ResetScrollSizes();
		InvalidateRect(nullptr);
	}
}


void CSketcherView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	CScrollView::OnPrepareDC(pDC, pInfo);
	CSketcherDoc* pDoc{ GetDocument() };
	pDC->SetMapMode(MM_ANISOTROPIC);			// Set the map mode
	CSize DocSize{ pDoc->GetDocSize() };		// Get the document size

	pDC->SetWindowExt(DocSize);					// Now set the window extent

	// Get the number of pixels per inch in x and y
	int xLogPixels{ pDC->GetDeviceCaps(LOGPIXELSX) };
	int yLogPixels{ pDC->GetDeviceCaps(LOGPIXELSY) };

	// Calculate the viewport extent in x and y for the current scale
	int xExtent{ (DocSize.cx * m_Scale * xLogPixels) / 100 };
	int yExtent{ (DocSize.cy * m_Scale * yLogPixels) / 100 };

	pDC->SetViewportExt(xExtent, yExtent);		// Set viewport extent
}


void CSketcherView::ResetScrollSizes()
{
	CClientDC aDC{ this };
	OnPrepareDC(&aDC);								// Set up the device context
	CSize DocSize{ GetDocument()->GetDocSize() };	// Get the document size
	aDC.LPtoDP(&DocSize);							// Get the size in pixels
	SetScrollSizes(MM_TEXT, DocSize);				// Set up the scrollbars
}


void CSketcherView::OnUpdateScale(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
	CString scaleStr;
	scaleStr.Format(_T(" View Scale : %d"), m_Scale);
	pCmdUI->SetText(scaleStr);
}
