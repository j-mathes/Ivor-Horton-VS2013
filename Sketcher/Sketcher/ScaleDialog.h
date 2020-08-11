#pragma once
#include "afxcmn.h"


// CScaleDialog dialog

class CScaleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CScaleDialog)

public:
	CScaleDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScaleDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCALE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Stores the current view scale
	int m_Scale;
	// Spin control for view scale
	CSpinButtonCtrl m_Spin;
	virtual BOOL OnInitDialog();
};
