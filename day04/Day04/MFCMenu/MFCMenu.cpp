#include <afxwin.h>
#include <afxdlgs.h>
#include "resource.h"
// 2. ��ܴ�����
class CMyFrameWnd:public CFrameWnd{
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNew();
	afx_msg void OnOpen();
	afx_msg void OnExit();
	afx_msg void OnNewUpdateCmdUI(CCmdUI* pCmdUI);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	CMenu m_Menu; // �˵�����
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
//	ON_COMMAND(ID_NEW,OnNew)
	ON_COMMAND(ID_OPEN,OnOpen)
	ON_COMMAND(ID_EXIT,OnExit)
	ON_UPDATE_COMMAND_UI(ID_NEW,OnNewUpdateCmdUI)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CMyFrameWnd::OnContextMenu(CWnd* pWnd, CPoint pos)
{
	// 1. ���ز˵���Դ
	CMenu menu;
	menu.LoadMenu(IDR_MENU2);
	// 2. ��ȡ�Ӳ˵�
	CMenu* pMenu = menu.GetSubMenu(0);
	// 3. ��ʾ
	pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN,pos.x,pos.y,this);
}

void CMyFrameWnd::OnNewUpdateCmdUI(CCmdUI* pCmdUI)
{
//	pCmdUI->Enable(FALSE);  // ���ò˵��� ����
//	pCmdUI->SetCheck(TRUE); // ���ò˵��� ��ѡ
	pCmdUI->SetRadio(TRUE); // ���ò˵��� ��ѡ
	pCmdUI->SetText("�½��ĵ�"); // ���Ĳ˵�����ı�
}
void CMyFrameWnd::OnExit()
{
	PostQuitMessage(0);
}
void CMyFrameWnd::OnOpen()
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();
}
void CMyFrameWnd::OnNew()
{
	AfxMessageBox("CMyFrameWnd::OnNew");
}
int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// ��Ӳ˵�
	// 1. ���ز˵�
	m_Menu.LoadMenu(IDR_MENU1);
	// 2. ���˵����õ�����
	SetMenu(&m_Menu);
	return 0;
}

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
	AfxMessageBox("CMyWinApp::OnNew");
}
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyFrameWnd* pFrame = new CMyFrameWnd;
	pFrame->Create(NULL,"MFCMenu");
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}