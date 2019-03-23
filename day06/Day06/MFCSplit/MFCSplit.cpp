#include <afxwin.h>
#include <afxext.h>
#include <afxhtml.h>
#include "resource.h"
// 3. ��ͼ�� ( ֧�ֶ�̬���� )
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
// 2. ��ܴ�����
class CMyFrameWnd:public CFrameWnd{
public:
	virtual BOOL OnCreateClient( LPCREATESTRUCT lpcs, 
		CCreateContext* pContext );
	CSplitterWnd m_wndSplit; // �����зֶ���
};
BOOL CMyFrameWnd::OnCreateClient( LPCREATESTRUCT lpcs, CCreateContext* pContext )
{
	// ��̬�зִ���
	// 1. ������̬�зִ���
/*	m_wndSplit.CreateStatic(this,1,2);
	// 2. ������ͼ
	m_wndSplit.CreateView(0,0,RUNTIME_CLASS(CMyView),
		CSize(200,200),pContext);
	m_wndSplit.CreateView(0,1,RUNTIME_CLASS(CHtmlView),
		CSize(200,200),pContext);
	// 3. ��������������ȡ��ͼ����
	CHtmlView* pHtmlView = (CHtmlView*)m_wndSplit.GetPane(0,1);
	// 4. ������ָ��ҳ��
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

	// ��̬�зִ���
	CCreateContext cxt;
	cxt.m_pNewViewClass = RUNTIME_CLASS(CEditView);
	m_wndSplit.Create(this,2,2,CSize(1,1),&cxt);

	return TRUE;
}
// 1. Ӧ�ó�����
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