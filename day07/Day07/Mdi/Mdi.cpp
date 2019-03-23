#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
// 5. �ĵ��� (֧�ֶ�̬����)
class CMyDoc:public CDocument{
public:
	CString m_strData;  // ���ڱ�����ͼ������
DECLARE_DYNCREATE(CMyDoc)
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
// 4. ��ͼ�� (֧�ֶ�̬����)
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
	// 1. ��ȡ�ͻ��ͼ�������ĵ�
	CMyDoc* pDoc = (CMyDoc*)GetDocument();
	// 2. �����ͼ�е����ݱ������ĵ���
	GetWindowText(pDoc->m_strData);
	// 3. �ĵ�֪ͨ������ͼ���ݱ�������
	pDoc->UpdateAllViews(this);
}
void CMyView::OnUpdate( CView* pSender, LPARAM lHint, CObject* pHint )
{
	// 4. ��ȡ�������ĵ�
	CMyDoc* pDoc = (CMyDoc*)GetDocument();
	// 5. ��ȡ�ĵ������ݣ��ŵ���ͼ������
	SetWindowText(pDoc->m_strData);
}
// 3. ���ĵ����ӿ�ܴ����� (֧�ֶ�̬����)
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
	// 1. ��ȡ���ͼ��Ӧ���ĵ�
	CDocument* pDoc =  GetActiveDocument();
	// 2. �����ĵ���ȡ�ĵ�ģ��
	CDocTemplate* pTemplate = pDoc->GetDocTemplate();
	// 3. ʹ��ģ����ú��������µ��ӿ�ܴ���
	CFrameWnd* pChildFrame = pTemplate->CreateNewFrame(pDoc,NULL);
	// 4. ��ʼ�����¿��
	pChildFrame->InitialUpdateFrame(pDoc,TRUE);
}

// 2. ���ĵ�������ܴ�����
class CMainFrame:public CMDIFrameWnd{
};
// 1. Ӧ�ó�����
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