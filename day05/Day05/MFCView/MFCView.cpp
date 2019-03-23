#include <afxwin.h>
#include "resource.h"
// 3. 视图类
class CMyView:public CView
{
public:
	virtual void OnDraw( CDC* pDC );
protected:
	afx_msg void OnNew();
	afx_msg void OnPaint();
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyView,CView)
//	ON_COMMAND(ID_NEW,OnNew)
//	ON_WM_PAINT()
END_MESSAGE_MAP()
void CMyView::OnPaint()
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint( m_hWnd,&ps );
	::TextOut(hdc,10,10,"Hello OnPaint",13);
	::EndPaint(m_hWnd,&ps);
}
void CMyView::OnDraw( CDC* pDC )
{
	pDC->TextOut(100,100,"Hello OnDraw");
}
void CMyView::OnNew()
{
	AfxMessageBox("CMyView::OnNew");
}

// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd{
public:
//	CMyView m_wndView;  // 视图对象
	CMyView* m_pWndView;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
//	ON_WM_SIZE()
END_MESSAGE_MAP()

void CMyFrameWnd::OnSize(UINT nType, int cx, int cy)
{
	m_pWndView->MoveWindow(0,0,cx,cy);
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// 创建视图窗口
/*	m_wndView.Create(NULL,"MFCView",WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(0,0,200,200),this,1000);*/
	m_pWndView = new CMyView;
	m_pWndView->Create(NULL,"MFCView",WS_CHILD|WS_VISIBLE|WS_BORDER,
		CRect(0,0,200,200),this,AFX_IDW_PANE_FIRST);
	// 设置为活动视图
//	SetActiveView(m_pWndView);
	m_pViewActive = m_pWndView;
	return 0;
}
// 1. 应用程序类
class CMyWinApp:public CWinApp{
public:
	virtual BOOL InitInstance();
	afx_msg void OnNew();
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
	ON_COMMAND(ID_NEW,OnNew)
END_MESSAGE_MAP()
void CMyWinApp::OnNew()
{
	AfxMessageBox("CMyWinApp::OnNew");
}
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance(){
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->LoadFrame(IDR_MENU1);
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}