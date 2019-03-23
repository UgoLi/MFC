#include <afxwin.h>
#include "resource.h"
// 1 对话框类
class CMyDlg:public CDialog
{
public:
	CMyDlg():CDialog(IDD_DIALOG1){}
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
void CMyDlg::OnOK()
{
	DestroyWindow();
}
void CMyDlg::OnCancel()
{
	DestroyWindow();
}
void CMyDlg::PostNcDestroy()
{
	delete this;
}
// 2 应用程序类
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;//全局的应用程序对象
BOOL CMyWinApp::InitInstance()
{
	/*
	// 模式对话框
	// 1 创建对话框对象
	CMyDlg dlg;
	// 2 将dlg作为程序的主窗口对象
	m_pMainWnd=&dlg;
	// 3 创建和显示对话框
	dlg.DoModal();
	*/
	// 非模式对话框
	CMyDlg* pDlg=new CMyDlg;
	pDlg->Create(IDD_DIALOG1);
	m_pMainWnd=pDlg;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;

}
