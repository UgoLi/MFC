#include <afxwin.h>  // windows.h + afx.h
// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd{};
// 1. 应用程序类
class CMyWinApp:public CWinApp{
public:
	virtual BOOL InitInstance();
	virtual int Run( );
//	virtual BOOL OnIdle( LONG lCount );
//	virtual int ExitInstance( );
};
CMyWinApp theApp;
int CMyWinApp::Run()
{
	AfxMessageBox("消息循环");
	return CWinApp::Run();
}
BOOL CMyWinApp::InitInstance(){
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCBase");
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}