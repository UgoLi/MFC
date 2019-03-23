#include <afxwin.h>
#include <afxext.h>
#include "resource.h"
UINT g_Indicators[] = 
{
	0,
	IDS_TIME,
	ID_INDICATOR_CAPS,  // ��д������(CapsLock)��״̬
	ID_INDICATOR_NUM    // С���̵�������������״̬
};
// 2. ��ܴ�����
class CMyFrameWnd:public CFrameWnd
{
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNew();
	afx_msg void OnToolBar();
	afx_msg void OnToolBarUpdateCmdUI(CCmdUI* pcmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CToolBar m_wndToolBar; // ���������� <afxext.h>
	CStatusBar m_wndStatusBar; // ״̬������
DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMyFrameWnd,CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_NEW,OnNew)
	ON_COMMAND(ID_TOOLBAR,OnToolBar)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR,OnToolBarUpdateCmdUI)
	ON_WM_TIMER()
END_MESSAGE_MAP()
void CMyFrameWnd::OnTimer(UINT_PTR nIDEvent)
{
	SYSTEMTIME st;
	::GetLocalTime(&st);
	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d\n",
		st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	m_wndStatusBar.SetPaneText(1,strTime);
}
void CMyFrameWnd::OnToolBarUpdateCmdUI(CCmdUI* pcmdUI)
{
	pcmdUI->SetCheck(m_wndToolBar.IsVisible());
}
void CMyFrameWnd::OnToolBar()
{
/*	if(m_wndToolBar.IsVisible())
	{
		ShowControlBar(&m_wndToolBar,FALSE,FALSE);
	}
	else
	{
		ShowControlBar(&m_wndToolBar,TRUE,FALSE);
	}*/
	ShowControlBar(&m_wndToolBar,!m_wndToolBar.IsVisible(),FALSE);
}
void CMyFrameWnd::OnNew()
{
	AfxMessageBox("CMyFrameWnd::OnNew");
}

int CMyFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// ����������
	// 1. ��������������
	m_wndToolBar.Create(this,WS_CHILD|WS_VISIBLE|CBRS_TOP);
	// 2. ���ع�������Դ
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR1);
	// 3. ͣ�������� (���뻯)
	// 3.1 ���ù���������ͣ��
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	// 3.2 ���ÿ�ܴ�������ͣ��
	EnableDocking(CBRS_ALIGN_ANY);
	// 3.3 ͣ��������
	DockControlBar(&m_wndToolBar,AFX_IDW_DOCKBAR_TOP);

	// ����״̬��
	// 1. ����״̬������
	m_wndStatusBar.Create(this);
	// 2. ����״̬��ָʾ��
	m_wndStatusBar.SetIndicators(g_Indicators,
		sizeof(g_Indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(1,IDS_TIME,SBPS_NOBORDERS,200);

	// ���ö�ʱ��
	::SetTimer(m_hWnd,1001,1000,NULL);

	return 0;
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
	pFrame->Create(NULL,"MFCBar",WS_OVERLAPPEDWINDOW,
		CFrameWnd::rectDefault,NULL,(char*)IDR_MENU1);
	m_pMainWnd = pFrame;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}