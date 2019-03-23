// 定义消息
#define WM_MYMESSAGE WM_USER + 1001
#include <afxwin.h>
// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd{
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTest();
	afx_msg void OnTestRange( UINT nID);
	afx_msg void OnEnChange();
	afx_msg LRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(1000,OnTest)
	ON_COMMAND_RANGE(1006,1008,OnTestRange)
	ON_EN_CHANGE(1010,OnEnChange)
	ON_MESSAGE(WM_MYMESSAGE,OnMyMessage) // 自定义消息宏
END_MESSAGE_MAP()
int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	::CreateWindow("BUTTON","测试",WS_CHILD|WS_VISIBLE,100,100,100,40,
		m_hWnd,(HMENU)1000,AfxGetInstanceHandle(),NULL);

	::CreateWindow("BUTTON","测试1",WS_CHILD|WS_VISIBLE,100,180,100,40,
		m_hWnd,(HMENU)1006,AfxGetInstanceHandle(),NULL);
	::CreateWindow("BUTTON","测试2",WS_CHILD|WS_VISIBLE,100,260,100,40,
		m_hWnd,(HMENU)1007,AfxGetInstanceHandle(),NULL);
	::CreateWindow("BUTTON","测试3",WS_CHILD|WS_VISIBLE,100,340,100,40,
		m_hWnd,(HMENU)1008,AfxGetInstanceHandle(),NULL);

	::CreateWindow("EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,300,100,100,100,
		m_hWnd,(HMENU)1010,AfxGetInstanceHandle(),NULL);

	return 0;
}
void CMyFrameWnd::OnTest()
{
//	AfxMessageBox("测试按钮被点击");
	// 发送一个自定义消息
	SendMessage(WM_MYMESSAGE,(WPARAM)"编程",(LPARAM)"快乐");
}
void CMyFrameWnd::OnTestRange(UINT nID)
{
	CString strID;
	strID.Format("%d\n",nID);
	AfxMessageBox(strID);
}
void CMyFrameWnd::OnEnChange()
{
	CWnd* pWnd = GetDlgItem(1010);
	CString strText;
	pWnd->GetWindowText(strText);
	AfxMessageBox(strText);
}
LRESULT CMyFrameWnd::OnMyMessage(WPARAM wParam,LPARAM lParam)
{
	CString strText;
	strText.Format("%s使我%s\n",wParam,lParam);
	AfxMessageBox(strText);
	return 0;
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
	pFrame->Create(NULL,"MFCMsgType");
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}