#include <afxwin.h>
// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd
{
public:
//	virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
//DECLARE_MESSAGE_MAP()

protected: 
	static const AFX_MSGMAP* PASCAL GetThisMessageMap(); 
	virtual const AFX_MSGMAP* GetMessageMap() const; 
};
/*BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()*/

PTM_WARNING_DISABLE 
const AFX_MSGMAP* CMyFrameWnd::GetMessageMap() const 
{ 
	return GetThisMessageMap(); 
} 
const AFX_MSGMAP* PASCAL CMyFrameWnd::GetThisMessageMap() 
{ 
	typedef CMyFrameWnd ThisClass;						   
	typedef CFrameWnd TheBaseClass;					   
	static const AFX_MSGMAP_ENTRY _messageEntries[] =  
	{
		{ WM_CREATE, 0, 0, 0, AfxSig_is, 
		(AFX_PMSG) (AFX_PMSGW) 
		(static_cast< int (AFX_MSG_CALL CWnd::*)(LPCREATESTRUCT) > ( &ThisClass :: OnCreate)) },

		{ WM_PAINT, 0, 0, 0, AfxSig_vv, 
		(AFX_PMSG)(AFX_PMSGW) 
		(static_cast< void (AFX_MSG_CALL CWnd::*)(void) > ( &ThisClass :: OnPaint)) },

		{0, 0, 0, 0, AfxSig_end, (AFX_PMSG)0 } 
	}; 
	static const AFX_MSGMAP messageMap = 
		{ &TheBaseClass::GetThisMessageMap, &_messageEntries[0] }; 
	return &messageMap; 
}								  
PTM_WARNING_RESTORE


int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	AfxMessageBox("CMyFrameWnd::OnCreate");
	return 0;
}
void CMyFrameWnd::OnPaint()
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint( m_hWnd, &ps );
	::TextOut( hdc, 100, 100, "Hello", 5 );
	::EndPaint( m_hWnd, &ps );
}

/*LRESULT CMyFrameWnd::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_CREATE:
		AfxMessageBox("OnCreate");
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {0};
			HDC hdc = ::BeginPaint( m_hWnd, &ps );
			::TextOut( hdc, 100, 100, "Hello", 5 );
			::EndPaint( m_hWnd, &ps );
		}
		break;
	}
	return CFrameWnd::WindowProc( message, wParam, lParam );
}
*/
// 1. 应用程序类
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCMsgMap");
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}