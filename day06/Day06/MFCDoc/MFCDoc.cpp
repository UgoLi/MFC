#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
// 4. 文档类
class CMyDoc:public CDocument
{
public:
	CMyDoc(){
		m_strData = "Hello Data";
	}
	CString m_strData;
	afx_msg void OnNew();
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyDoc,CDocument)
//	ON_COMMAND(ID_NEW,OnNew)
END_MESSAGE_MAP()
void CMyDoc::OnNew()
{
	AfxMessageBox("CMyDoc::OnNew");
}
// 3. 视图类 (支持动态创建)
class CMyView:public CEditView
{
public:
	virtual void OnInitialUpdate( );	
DECLARE_DYNCREATE(CMyView)
};
void CMyView::OnInitialUpdate()
{
	// 1. 获取与视图关联的文档
	CMyDoc* pDoc = (CMyDoc*)GetDocument();
	// 2. 将文档的数据显示在视图窗口上
	SetWindowText(pDoc->m_strData);
}
IMPLEMENT_DYNCREATE(CMyView,CEditView)
// 2. 框架窗口类
class CMyFrameWnd:public CFrameWnd{};
// 1.应用程序类
class CMyWinApp:public CWinApp
{
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
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;

	CCreateContext cxt;
	cxt.m_pNewViewClass = RUNTIME_CLASS(CMyView);
	cxt.m_pCurrentDoc = new CMyDoc;
	pFrame->LoadFrame(IDR_MENU1,WS_OVERLAPPEDWINDOW,NULL,&cxt);
	pFrame->InitialUpdateFrame(NULL,TRUE);

	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}