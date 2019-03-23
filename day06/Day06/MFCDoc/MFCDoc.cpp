#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
// 4. �ĵ���
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
// 3. ��ͼ�� (֧�ֶ�̬����)
class CMyView:public CEditView
{
public:
	virtual void OnInitialUpdate( );	
DECLARE_DYNCREATE(CMyView)
};
void CMyView::OnInitialUpdate()
{
	// 1. ��ȡ����ͼ�������ĵ�
	CMyDoc* pDoc = (CMyDoc*)GetDocument();
	// 2. ���ĵ���������ʾ����ͼ������
	SetWindowText(pDoc->m_strData);
}
IMPLEMENT_DYNCREATE(CMyView,CEditView)
// 2. ��ܴ�����
class CMyFrameWnd:public CFrameWnd{};
// 1.Ӧ�ó�����
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