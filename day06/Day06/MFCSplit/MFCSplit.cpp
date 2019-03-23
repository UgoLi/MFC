#include <afxwin.h>
#include <afxext.h>
#include <afxhtml.h>
#include "resource.h"
// 3. 视图类 ( 支持动态创建 )
class CMyView:public CView
{
public:
	virtual void OnDraw(CDC* pDC);
DECLARE_DYNCREATE(CMyView)
};
IMPLEMENT_DYNCREATE(CMyView,CView)
void CMyView::OnDraw(CDC* pDC)
{
	pDC->TextOut(10,10,"Hello CMyView");
}
// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd{
public:
	virtual BOOL OnCreateClient( LPCREATESTRUCT lpcs, 
		CCreateContext* pContext );
	CSplitterWnd m_wndSplit; // 窗口切分对象
};
BOOL CMyFrameWnd::OnCreateClient( LPCREATESTRUCT lpcs, CCreateContext* pContext )
{
	// 静态切分窗口
	// 1. 创建静态切分窗口
/*	m_wndSplit.CreateStatic(this,1,2);
	// 2. 创建视图
	m_wndSplit.CreateView(0,0,RUNTIME_CLASS(CMyView),
		CSize(200,200),pContext);
	m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CHtmlView),
		CSize(200,200),pContext);
	// 3. 根据行列索引获取视图对象
	CHtmlView* pHtmlView = (CHtmlView*)m_wndSplit.GetPane(0,1);
	// 4. 导航到指定页面
//	pHtmlView->Navigate("https://www.tmooc.cn");
	pHtmlView->Navigate("C:/");
*/
/*	m_wndSplit.CreateStatic(this,3,3);
	CRect rt;
	GetClientRect(&rt);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			m_wndSplit.CreateView(i,j,RUNTIME_CLASS(CMyView),
				CSize(rt.Width()/3,rt.Height()/3),pContext);
		}
	}*/

	// 动态切分窗口
	CCreateContext cxt;
	cxt.m_pNewViewClass = RUNTIME_CLASS(CEditView);
	m_wndSplit.Create(this,2,2,CSize(1,1),&cxt);

	return TRUE;
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
	pFrame->LoadFrame(IDR_MENU1);
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}