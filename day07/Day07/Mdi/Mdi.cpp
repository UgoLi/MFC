#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
// 5. 文档类 (支持动态创建)
class CMyDoc:public CDocument{
public:
	CString m_strData;  // 用于保存活动视图的数据
DECLARE_DYNCREATE(CMyDoc)
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
// 4. 视图类 (支持动态创建)
class CMyView:public CEditView{
public:
	virtual void OnUpdate( CView* pSender, LPARAM lHint,
		CObject* pHint );
protected:
	afx_msg void OnEnChange();
DECLARE_DYNCREATE(CMyView)
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyView,CEditView)
	ON_CONTROL_REFLECT(EN_CHANGE,OnEnChange)
END_MESSAGE_MAP()
IMPLEMENT_DYNCREATE(CMyView,CEditView)
void CMyView::OnEnChange()
{
	// 1. 获取和活动视图关联的文档
	CMyDoc* pDoc = (CMyDoc*)GetDocument();
	// 2. 将活动视图中的数据保存在文档中
	GetWindowText(pDoc->m_strData);
	// 3. 文档通知其他视图数据被更新了
	pDoc->UpdateAllViews(this);
}
void CMyView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	// 4. 获取关联的文档
	CMyDoc* pDoc = (CMyDoc*)GetDocument();
	// 5. 获取文档的数据，放到视图窗口中
	SetWindowText(pDoc->m_strData);
}
// 3. 多文档的子框架窗口类 (支持动态创建)
class CChildFrame:public CMDIChildWnd{
protected:
	afx_msg void OnNewWnd();
DECLARE_DYNCREATE(CChildFrame)
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CChildFrame,CMDIChildWnd)
	ON_COMMAND(ID_NEWWND,OnNewWnd)
END_MESSAGE_MAP()
IMPLEMENT_DYNCREATE(CChildFrame,CMDIChildWnd)
void CChildFrame::OnNewWnd()
{
	// 1. 获取活动视图对应的文档
	CDocument* pDoc =  GetActiveDocument();
	// 2. 根据文档获取文档模板
	CDocTemplate* pTemplate = pDoc->GetDocTemplate();
	// 3. 使用模板调用函数创建新的子框架窗口
	CFrameWnd* pChildFrame = pTemplate->CreateNewFrame(pDoc,NULL);
	// 4. 初始化更新框架
	pChildFrame->InitialUpdateFrame(pDoc,TRUE);
}

// 2. 多文档的主框架窗口类
class CMainFrame:public CMDIFrameWnd{
};
// 1. 应用程序类
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
protected:
	afx_msg void OnNew();
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
	ON_COMMAND(ID_NEW,OnNew)
END_MESSAGE_MAP()
void CMyWinApp::OnNew()
{
	OnFileNew();
}
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMainFrame* pFrame = new CMainFrame;
	pFrame->LoadFrame(IDR_MAINFRAME);
	m_pMainWnd = pFrame;

	CMultiDocTemplate* pTemplate = new CMultiDocTemplate(
		IDR_CHILDFRAME,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(CMyView));
	AddDocTemplate(pTemplate);
	OnFileNew();

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}