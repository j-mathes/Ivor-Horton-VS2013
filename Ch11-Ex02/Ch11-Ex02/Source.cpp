#include <afxwin.h>							// For the class library

class COurApp : public CWinApp
{
public:
	virtual BOOL InitInstance() override;
};

class COurWnd : public CFrameWnd
{
public:
	// Constructor
	COurWnd()
	{
		Create(nullptr, _T("Our Dumb MFC Application"));
	}
};

BOOL COurApp::InitInstance(void)
{
	m_pMainWnd = new COurWnd;			// Construct a new window object
	m_pMainWnd->ShowWindow(m_nCmdShow);	// ... and display it
	return TRUE;
}

COurApp AnApplication;						// Define an application object