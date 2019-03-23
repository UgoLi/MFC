#include <afxwin.h>
#include "resource.h"
// 1 �Ի�����
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
// 2 Ӧ�ó�����
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;//ȫ�ֵ�Ӧ�ó������
BOOL CMyWinApp::InitInstance()
{
	/*
	// ģʽ�Ի���
	// 1 �����Ի������
	CMyDlg dlg;
	// 2 ��dlg��Ϊ����������ڶ���
	m_pMainWnd=&dlg;
	// 3 ��������ʾ�Ի���
	dlg.DoModal();
	*/
	// ��ģʽ�Ի���
	CMyDlg* pDlg=new CMyDlg;
	pDlg->Create(IDD_DIALOG1);
	m_pMainWnd=pDlg;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;

}
