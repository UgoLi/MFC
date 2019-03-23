#include <afxwin.h>
// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd{
public:
	virtual BOOL PreCreateWindow( CREATESTRUCT& cs  );
	virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM );
};
LRESULT CMyFrameWnd::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case WM_PAINT:
		{
			PAINTSTRUCT ps = {0};
			HDC hdc = ::BeginPaint( m_hWnd, &ps );
			::TextOut( hdc, 100, 100, "Hello", 5);
			::EndPaint( m_hWnd, &ps );
		}
		break;
	case WM_CREATE:
		AfxMessageBox("OnCreate");
		break;
	}
	return CFrameWnd::WindowProc(message,wParam,lParam);
}
BOOL CMyFrameWnd::PreCreateWindow( CREATESTRUCT& cs )
{
	cs.x = 100;
	cs.y = 100;
	cs.cx = 500;
	cs.cy = 350;
	return CFrameWnd::PreCreateWindow( cs );
}
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
	pFrame->Create(NULL,"MFCCreate");
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}