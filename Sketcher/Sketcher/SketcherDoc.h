
// SketcherDoc.h : interface of the CSketcherDoc class


#include "ElementType.h"
#include "ElementColor.h"
#include "Element.h"
#include <list>
#include <memory>

using SketchIterator = std::list<std::shared_ptr<CElement>>::const_iterator;

#pragma once

class CSketcherDoc : public CDocument
{
protected: // create from serialization only
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

// Attributes
public:

// Operations
public:
	ElementType GetElementType()const { return m_Element; }			// Not sure if these are in the correct spot
	ElementColor GetElementColor()const { return m_Color; }			// page 652
	int GetPenWidth() const { return m_PenWidth; }					// Get current pen width

	// Provide a begin iterator for the sketch
	SketchIterator begin() const { return std::begin(m_Sketch); }

	// Provide an end iterator for the sketch
	SketchIterator end() const { return std::end(m_Sketch); }

	// Finds the element under the point
	std::shared_ptr<CElement> FindElement(const CPoint& point) const
	{
		for (const auto& pElement : m_Sketch)
		{
			if (pElement->GetEnclosingRect().PtInRect(point))
				return pElement;
		}
		return nullptr;
	}

	void SendToBack(std::shared_ptr<CElement>& pElement)
	{
		if (pElement)
		{
			m_Sketch.remove(pElement);								// Remove the element from the list
			m_Sketch.push_back(pElement);							// Put it back at the end of the list
		}
	}

protected:
	int m_PenWidth{};												// Current pen width
	CSize m_DocSize{ CSize{ 3000,3000 } };							// Document size

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Add a sketch element
	void AddElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.push_back(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());					// Tell all of the views about the added element
	}
	
	// Delete a sketch element
	void DeleteElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.remove(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());					// Tell all of the views about the deleted element
	}

	// Get the line style
	int GetLineStyle()
	{
		return m_PenStyle;
	}

	CSize GetDocSize() const { return m_DocSize; }					// Retrieve the document size

protected:


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColorBlack();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnElementCircle();
	afx_msg void OnElementCurve();
protected:
	// Current element type
	ElementType m_Element{ ElementType::LINE };				// Current element type
	ElementColor m_Color{ ElementColor::BLACK };			// Current drawing color
	int m_PenStyle{ PS_SOLID };								// Current pen style
	std::list<std::shared_ptr<CElement>> m_Sketch;			// A list containing the sketch

public:

	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
	afx_msg void OnElementEllipse();
	afx_msg void OnUpdateElementEllipse(CCmdUI *pCmdUI);
	afx_msg void OnPenstyleSolid();
	afx_msg void OnPenstyleDashed();
	afx_msg void OnPenstyleDotted();
	afx_msg void OnPenstyleDashDotted();
	afx_msg void OnPenstyleDashDotDotted();
	afx_msg void OnUpdatePenstyleSolid(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenstyleDashed(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenstyleDotted(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenstyleDashDotted(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePenstyleDashDotDotted(CCmdUI *pCmdUI);
	afx_msg void OnPenWidth();
	afx_msg void OnElementText();
	afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);
};
