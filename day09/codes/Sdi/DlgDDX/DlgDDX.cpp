#include <afxwin.h>
#include "resource.h"
// 1 对话框
class CMyDlg:public CDialog
{
public:
	CMyDlg():CDialog(IDD_DIALOG1){}
	//对话框的初始化函数
	virtual BOOL OnInitDialog( );
	// 变量与控件的绑定
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual void OnOK();

public:
	CButton m_wndOK;//控件类型的成员变量
	CString m_strEdit;//值类型的成员变量
};
void CMyDlg::OnOK()
{
	UpdateData(TRUE);
	AfxMessageBox(m_strEdit);
}
void CMyDlg::DoDataExchange( CDataExchange* pDX )
{
	CDialog::DoDataExchange(pDX);
	// 控件与变量的绑定
	DDX_Control(pDX,IDOK,m_wndOK);
	DDX_Text(pDX,IDC_EDIT1,m_strEdit);
}
BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 控件的初始化
	// 将取消按钮的文本修改为取消操作
	CWnd* pWnd=GetDlgItem(IDCANCEL);
	pWnd->SetWindowText("取消操作");
	// 将确定的文本修改为执行操作
	m_wndOK.SetWindowText("执行操作");
	// 修改确定按钮的位置大小
	m_wndOK.MoveWindow(0,0,100,40);

	// 将编辑控件的初始值设为HelloWorld
	m_strEdit="HelloWorld";
	UpdateData(FALSE);
	return TRUE;
}
class CMyWinApp:public CWinApp
{
public:
	virtual BOOL InitInstance();
};
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMyDlg dlg;
	m_pMainWnd=&dlg;
	dlg.DoModal();
	return TRUE;
}